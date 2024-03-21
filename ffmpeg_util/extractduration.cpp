#include "ffmpeg_util/extractduration.h"

int MediaDurationTool::extractDuration(const QString &videoPath, int64_t *duration, double *fps) {
    AVFormatContext *formatContext = NULL;
    int err;

    AVDictionary *format_opts = NULL;
    av_dict_set(&format_opts, "probesize", "32", 0);

    // 打开视频文件
    if ((err = avformat_open_input(&formatContext, videoPath.toStdString().c_str(), NULL, NULL)) < 0) {
        // 处理错误...
        return err;
    }

    // 检索流信息
    if ((err = avformat_find_stream_info(formatContext, NULL)) < 0) {
        // 处理错误...
        avformat_close_input(&formatContext);
        return err;
    }
    double duration_in_seconds;

    // 获取视频时长（如果存在）
    if (formatContext->duration != AV_NOPTS_VALUE) {
        int64_t duration_in_microseconds = formatContext->duration; // 微秒
        duration_in_seconds = (double)duration_in_microseconds / AV_TIME_BASE;
    }
    else {
        return -1;
    }

    AVStream *videoStream = NULL;
    for (int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = formatContext->streams[i];
            break;
        }
    }

    int64_t estimatedTotalFrames;
    if (videoStream) {
        // 获取帧率（FPS）
        double _fps = av_q2d(videoStream->avg_frame_rate);
        if(fps)
            *fps = _fps;

        // 计算估算的总帧数
        estimatedTotalFrames = (int64_t)(duration_in_seconds * _fps);
        *duration = estimatedTotalFrames;
    }
    else {
        return -1;
    }

    // 清理
    avformat_close_input(&formatContext);

    return 0;
}
