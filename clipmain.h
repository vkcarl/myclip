#ifndef CLIPMAIN_H
#define CLIPMAIN_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class ClipMain; }
QT_END_NAMESPACE

class ClipMain : public QMainWindow
{
    Q_OBJECT

public:
    ClipMain(QWidget *parent = nullptr);
    ~ClipMain();

private:
    Ui::ClipMain *ui;

    // 创建视频播放器和视频显示控件
    QMediaPlayer *player;
    QVideoWidget *videoWidget;

    // 创建开始和暂停按钮
    QPushButton *playPauseButton = new QPushButton("Play");

    // 设置布局
    QVBoxLayout *layout;

    // 创建一个容器QWidget并设置为主窗口的中心控件
    QWidget *container;

private slots:
    // 自定义playPauseButton的槽函数
    void togglePlayPause();
};
#endif // CLIPMAIN_H
