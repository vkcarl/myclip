#include "videoplaywidget.h"
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>

bool VideoPlayWidget::event(QEvent *event) {
    qDebug() << "Received Event type:" << event->type();
    return QWidget::event(event);
}

VideoPlayWidget::VideoPlayWidget(QMediaPlayer *player, QPushButton *button, PlayerSlider *slider, QWidget *parent)
    : QVideoWidget(parent), _player(player), _button(button), _slider(slider) {
    setAcceptDrops(true);
    QWidget* child = qwindowChild();
    if (child) {
        child->installEventFilter(this);
    }
}

void VideoPlayWidget::dragEnterEvent(QDragEnterEvent* event) {
//    event->accept();
    if (event->mimeData()->hasFormat("text/plain")) { // 确保数据格式匹配
        event->acceptProposedAction();
    }
}

void VideoPlayWidget::dragMoveEvent(QDragMoveEvent* event) {
    // 通常你也想在这里接受动作，以便在拖动时给予用户反馈
    event->acceptProposedAction();
}

void VideoPlayWidget::dropEvent(QDropEvent* event) {
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasText()) {
        QString videoPath = mimeData->text();

        // 现在你有了视频路径，可以开始播放视频
        _player->setSource(QUrl::fromLocalFile(videoPath));
        _player->play(); // 开始播放
        _player->setPosition(0); // 将播放位置重置为开始
        _player->pause(); // 立即暂停，使得播放器停在第一帧
        _button->setText("Play");
        _slider->setEnabled(true);
    }
}

QWidget* VideoPlayWidget::qwindowChild() const {
    QWidget* child = findChild<QWidget*>(); // 默认查找第一个 QWidget 子对象
    if (child && QString(child->metaObject()->className()) == "QWindowContainer") {
        return child;
    }
    return nullptr;
}

bool VideoPlayWidget::eventFilter(QObject* obj, QEvent* event) {
    if (obj == qwindowChild()) {
        switch (event->type()) {
        case QEvent::DragEnter:
            qDebug() << "dragEnterEvent:" << event;
            return true;
            break;
        case QEvent::DragMove:
            qDebug() << "dragMoveEvent:" << event;
            return true;
            break;
        case QEvent::Drop:
            qDebug() << "dropEvent:" << event;
            return true;
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(obj, event);
}
