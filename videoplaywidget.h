#ifndef VIDEOPLAYWIDGET_H
#define VIDEOPLAYWIDGET_H
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include "playslider.h"

class VideoPlayWidget : public QVideoWidget {
public:
    VideoPlayWidget(QMediaPlayer *player, QPushButton *button, PlayerSlider *slider, QWidget *parent=nullptr);
protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    bool event(QEvent *event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    QMediaPlayer *_player;
    QPushButton *_button;
    PlayerSlider *_slider;
    QWidget* qwindowChild() const;
};

#endif // VIDEOPLAYWIDGET_H
