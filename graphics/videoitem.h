#ifndef VIDEOITEM_H
#define VIDEOITEM_H
#include<QGraphicsItem>
#include<QPixmap>
#include<QGraphicsScene>
#include "track.h"

class VideoItem : public QGraphicsItem {
public:
    VideoItem(const QString &videoPath, qreal duration);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
//    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
//    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
//    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    QPixmap *thumbnail;
    QString videoPath;
    qreal duration;
    QRectF rect;
    Q_DISABLE_COPY(VideoItem)
    bool is_mouse_pressed_;
//    QPixmap pic;
};

class VideoBlock {
public:
//    VideoBlock();
    ~VideoBlock();
    void PutVideoItem2Scene(QGraphicsScene *scene);
    void AddVideoItem(MediaTrackItem *item);
private:
    int numPerRow = 3; // 每行三个
    int spacing = 10; // 间距
    int itemWidth = 160; // 假设每个格子的宽度
    int itemHeight = 90; // 假设每个格子的高度
    std::vector<MediaTrackItem*> videoblock;
};


#endif // VIDEOITEM_H
