#ifndef TRACK_H
#define TRACK_H
#include<QGraphicsItem>

class MediaTrackItem : public QGraphicsItem {
public:
    // 构造函数
    MediaTrackItem(const QString &name, int duration, QGraphicsItem *parent = nullptr);

    // 必须重写的方法
    QRectF boundingRect() const override;    // 定义项的边界矩形
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;    // 定义如何绘制项

private:
    QPixmap *thumbnail;
    QPixmap scaledThumbnail;
    QString name;
    int duration;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif // TRACK_H
