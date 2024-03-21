#include "graphics/videoitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QWidget>
#include "ffmpeg_util/extractthumbnail.h"
#include <QPainter>


VideoItem::VideoItem(const QString &videoPath, qreal duration)
    : videoPath(videoPath), duration(duration) {
    // 提取缩略图
    rect = QRectF(0, 0, 160, 90);
    int err = ThumbnailTool::extractThumbnail(videoPath, &thumbnail, 0);
    if(err != 0)
    {
        exit(err);
    }
    QImage image = thumbnail->toImage();
    thumbnail->save("D:/x90pro/thumbnail.png");
}

QRectF VideoItem::boundingRect() const {
    // 返回该项的边界矩形，决定了绘制区域的大小
    return rect.adjusted(-1, -1, -1, -1); // 假设每个片段的大小为100x50
}

void VideoItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//    // 绘制项的外观
//    Q_UNUSED(option);
//    Q_UNUSED(widget);

//    QPixmap scaledThumbnail = thumbnail->scaled(rect.width(), rect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    painter->drawPixmap(rect.topLeft(), scaledThumbnail);

//    // 设置边框的颜色和宽度
//    QPen pen(Qt::green, 5); // 黑色边框，2个像素宽
//    painter->setPen(pen);

//    // 绘制边框
//    painter->drawRect(boundingRect());

    // 绘制项的外观
    painter->setPen(Qt::NoPen); // 不使用边框
    painter->setBrush(Qt::blue); // 使用蓝色填充
    painter->drawRect(boundingRect()); // 绘制矩形

    // 绘制文本
    painter->setPen(Qt::white); // 文本颜色为白色
    painter->drawText(boundingRect(), Qt::AlignCenter, "test"); // 在矩形中心绘制文本
}

void VideoItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // 标记开始拖动
    setZValue(1);
    VideoItem::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        is_mouse_pressed_ = true;
    }
}

void VideoItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (true) {
        VideoItem::mouseMoveEvent(event);
        QDrag *drag = new QDrag(event->widget());
        QMimeData *mimeData = new QMimeData;

        // 设置mime类型和数据，例如视频路径
        mimeData->setText(videoPath);
        drag->setMimeData(mimeData);

        // 开始拖放操作
        drag->exec();
    }
}

void VideoItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    VideoItem::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        is_mouse_pressed_ = false;
    }
    setZValue(0);
}

void VideoBlock::PutVideoItem2Scene(QGraphicsScene* scene) {
    for (int i = 0; i < videoblock.size(); ++i) {
        int row = i / numPerRow;
        int col = i % numPerRow;
        qreal x = col * (itemWidth + spacing);
        qreal y = row * (itemHeight + spacing);

        scene->addItem(videoblock[i]);
        videoblock[i]->setPos(x, y); // 假设videoItems是你的视频素材格子对象列表
    }
}

void VideoBlock::AddVideoItem(MediaTrackItem *item) {
    videoblock.push_back(item);
}

VideoBlock::~VideoBlock() {
    for(int i = 0; i < videoblock.size(); i++) {
        delete videoblock[i];
    }
}
