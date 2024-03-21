#include "extractthumbnail.h"

int ThumbnailTool::extractThumbnail(const QString &videoPath, QPixmap **vedioPixmap, int64_t start) {
    // 使用第三方库（如 FFmpeg）提取视频文件的缩略图
    // 返回一个 QPixmap 对象
    // ...
    int err;
    AVFormatContext* fmt_ctx = nullptr;
    int videoStreamIndex = -1;
    AVCodecContext* codecContext = nullptr;
    AVFrame* frame = nullptr;
    AVFrame* frameRGB = nullptr;
    AVPacket* packet = av_packet_alloc();
    AVFilterGraph *filter_graph = NULL;
    AVFilterContext *mainsrc_ctx,*resultsink_ctx = NULL;

    fmt_ctx = avformat_alloc_context();
    if (!fmt_ctx) {
        printf("error code %d \n",AVERROR(ENOMEM));
        return ENOMEM;
    }

    // 打开视频文件
    if(err = avformat_open_input(&fmt_ctx, videoPath.toStdString().c_str(), nullptr, nullptr) != 0) {
        // 处理错误
        printf("error code %d \n",err);
        return err;
    }

    // 寻找第一个视频流
    for(unsigned i = 0; i < fmt_ctx->nb_streams; i++) {
        if(fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if(videoStreamIndex == -1) {
        // 没有找到视频流
        printf("no video stream");
        return -1;
    }

    // 获取旋转信息
    AVDictionaryEntry *rotate_tag = av_dict_get(fmt_ctx->streams[videoStreamIndex]->metadata, "rotate", NULL, 0);
    int rotate = 0;
    if (rotate_tag != NULL) {
        rotate = atoi(rotate_tag->value);
    }

    // 获取解码器
    AVCodecParameters* codecParameters = fmt_ctx->streams[videoStreamIndex]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(codecParameters->codec_id);

    // 打开解码器
    codecContext = avcodec_alloc_context3(codec);
    if(err = avcodec_parameters_to_context(codecContext, codecParameters) < 0) {
        printf("error code %d \n",err);
        return err;
    }

    if(err = avcodec_open2(codecContext, codec, nullptr) < 0) {
        // 处理错误
        printf("error code %d \n",err);
        return err;
    }

    frame = av_frame_alloc();
    //    AVFrame *tmp_frame = av_frame_alloc();
    frameRGB = av_frame_alloc();

    // 设置RGB帧的格式和大小
    int numBytes;
    if((rotate / 90) % 2)
        numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecContext->height, codecContext->width, 1);
    else
        numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecContext->width, codecContext->height, 1);
    uint8_t* buffer = (uint8_t *)av_malloc(numBytes);
    if((rotate / 90) % 2)
        av_image_fill_arrays(frameRGB->data, frameRGB->linesize, buffer, AV_PIX_FMT_RGB24, codecContext->height, codecContext->width, 1);
    else
        av_image_fill_arrays(frameRGB->data, frameRGB->linesize, buffer, AV_PIX_FMT_RGB24, codecContext->width, codecContext->height, 1);
    int extractOk = 0;

    if(start != 0)  //不是提取视频开头图片的情况
    {
        // 定位读取位置
        int64_t seek_target;
        int64_t seek_min = INT64_MIN;
        int64_t seek_max = INT64_MAX;
        int flags = AVSEEK_FLAG_FRAME;
        if(start == -1) // 提取最后一帧附近的关键帧图片
            MediaDurationTool::extractDuration(videoPath.toStdString().c_str(), &seek_target, nullptr);
        else //要不要限制seek的位置，暂时不知道
            seek_target = start;    // start是帧数
        AVRational targetTimeBase = av_guess_frame_rate(fmt_ctx, fmt_ctx->streams[videoStreamIndex], NULL);
        int64_t targetTimestamp = av_rescale_q(seek_target, targetTimeBase, (AVRational){1, AV_TIME_BASE});
        err = avformat_seek_file(fmt_ctx, -1, seek_min, targetTimestamp, seek_max, flags);
        if(err < 0) {
            printf("error code %d \n",err);
            return err;
        }
    }

    // 读取帧
    while(av_read_frame(fmt_ctx, packet) >= 0) {
        if(extractOk == 1)
        {
            break;
        }
        if(packet->stream_index == videoStreamIndex) {
            // 解码视频帧
            avcodec_send_packet(codecContext, packet);
            av_packet_unref(packet);
            for(;;){
                //读取 AVFrame
                err = avcodec_receive_frame(codecContext, frame);
                /* 释放 frame 里面的YUV数据，
                 * 由于 avcodec_receive_frame 函数里面会调用 av_frame_unref，所以下面的代码可以注释。
                 * 所以我们不需要 手动 unref 这个 AVFrame
                 * */
                //av_frame_unref(frame);

                if( AVERROR(EAGAIN) == err ){
                    //提示 EAGAIN 代表 解码器 需要 更多的 AVPacket
                    //跳出 第一层 for，让 解码器拿到更多的 AVPacket
                    break;
                }
                else {
                    int ret = 0;
                    AVFilterInOut *inputs, *outputs;
                    int times = rotate / 90;

                    if(times > 0 && NULL == filter_graph){
                        //初始化滤镜
                        filter_graph = avfilter_graph_alloc();
                        if (!filter_graph) {
                            printf("Error: allocate filter graph failed\n");
                            return -1;
                        }

                        // 因为 filter 的输入是 AVFrame ，所以 filter 的时间基就是 AVFrame 的时间基
                        AVRational tb = fmt_ctx->streams[0]->time_base;
                        AVRational fr = av_guess_frame_rate(fmt_ctx, fmt_ctx->streams[videoStreamIndex], NULL);
                        AVRational sar = frame->sample_aspect_ratio;

                        AVBPrint args;
                        av_bprint_init(&args, 0, AV_BPRINT_SIZE_AUTOMATIC);
                        av_bprintf(&args,
                                   "buffer=video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d:frame_rate=%d/%d[main];"
                                   "[main]transpose=1[result];"
                                   "[result]buffersink",
                                   frame->width, frame->height, frame->format, tb.num,tb.den,sar.num, sar.den,fr.num, fr.den);

                        //解析滤镜字符串。
                        ret = avfilter_graph_parse2(filter_graph, args.str, &inputs, &outputs);
                        if (ret < 0) {
                            printf("Cannot configure graph\n");
                            return ret;
                        }

                        //正式打开滤镜
                        ret = avfilter_graph_config(filter_graph, NULL);
                        if (ret < 0) {
                            printf("Cannot configure graph\n");
                            return ret;
                        }

                        //根据 名字 找到 AVFilterContext
                        mainsrc_ctx = avfilter_graph_get_filter(filter_graph, "Parsed_buffer_0");
                        resultsink_ctx = avfilter_graph_get_filter(filter_graph, "Parsed_buffersink_2");
                    }
                    for(int i = 0; i < times; i++) {
                        ret = av_buffersrc_add_frame_flags(mainsrc_ctx, frame, AV_BUFFERSRC_FLAG_PUSH);
                        if(ret < 0){
                            printf("Error: av_buffersrc_add_frame failed\n");
                            return ret;
                        }

                        ret = av_buffersink_get_frame_flags(resultsink_ctx, frame, AV_BUFFERSRC_FLAG_PUSH);
                    }
                    if(times == 0 || ret >= 0 ){
                        // 将帧从原始格式转换为RGB
                        struct SwsContext* sws_ctx = sws_getContext(frame->width, frame->height, codecContext->pix_fmt, frame->width, frame->height, AV_PIX_FMT_RGB24, SWS_BILINEAR, nullptr, nullptr, nullptr);
                        sws_scale(sws_ctx, (uint8_t const* const*)frame->data, frame->linesize, 0, frame->height, frameRGB->data, frameRGB->linesize);
                        sws_freeContext(sws_ctx);
                        // 在此处处理frameRGB（例如，保存为图像文件）
//                        save_rgb_to_file(frameRGB, videoPath.toStdString().c_str());
                        QImage img(frameRGB->data[0], frame->width, frame->height, frameRGB->linesize[0], QImage::Format_RGB888);
                        // 转换为 QPixmap
                        QPixmap *pixmap = new QPixmap(QPixmap::fromImage(img));
                        *vedioPixmap = pixmap;
                        extractOk = 1;
                        break;
                    }
                }
            }
        }
    }
    av_frame_free(&frame);
    av_frame_free(&frameRGB);
    av_packet_free(&packet);
    //关闭编码器，解码器。
    avcodec_close(codecContext);

    //释放容器内存。
    avformat_free_context(fmt_ctx);
    return 0;
}
