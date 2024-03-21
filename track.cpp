#include "track.h"
#include <QPainter>
#include "ffmpeg_util/extractthumbnail.h"
#include <QPixmap>
#include <QGraphicsSceneEvent>
#include <QMimeData>
#include <QDrag>
#include <QWidget>

QRectF MediaTrackItem::boundingRect() const {
    // 返回该项的边界矩形，决定了绘制区域的大小
    return QRectF(0, 0, 160, 90); // 假设每个片段的大小为100x50
}

void MediaTrackItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(boundingRect().topLeft(), scaledThumbnail);
    // 设置绘制边框的画笔
    QPen pen(Qt::gray, 5); // 黑色画笔，5个像素宽
    painter->setPen(pen);

    // 绘制边框，大小与boundingRect一致
    painter->drawRect(boundingRect());


}

MediaTrackItem::MediaTrackItem(const QString &name, int duration, QGraphicsItem *parent)
    : QGraphicsItem(parent), name(name), duration(duration) {
    // 在这里可以进行一些初始化操作
    int err = ThumbnailTool::extractThumbnail(name, &thumbnail, 0);
    if(err != 0)
    {
        exit(err);
    }
    scaledThumbnail = thumbnail->scaled(boundingRect().width(), boundingRect().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 设置项的属性，例如可以接受悬停事件
    setAcceptHoverEvents(true);

//    setFlag(QGraphicsItem::ItemIsMovable, true);
}
void MediaTrackItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (event->widget() == nullptr) {
            // event->widget() 返回 nullptr，处理对应的情况
            qDebug() << "Mouse Press Event Received, but event->widget() is null";
        } else {
            // event->widget() 返回了有效的 QGraphicsView 指针，继续处理
            // 创建一个 QMimeData 对象来传递视频信息
            QMimeData* mimeData = new QMimeData();
            mimeData->setText(name); // 或者是其他能标识视频的信息

            // 创建一个 QDrag 对象
            QDrag* drag = new QDrag(event->widget());
            drag->setMimeData(mimeData);

            // 可以设置一个缩略图作为拖拽时显示的图像
            drag->setPixmap(scaledThumbnail);

            // 开始拖拽操作
            drag->exec();
        }

    }

    qDebug() << "Mouse Press Event Received";
    // 确保还调用基类的事件处理器
    QGraphicsItem::mousePressEvent(event);
    event->accept();
}

//void TrackItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
//    // 处理鼠标移动事件
//}
