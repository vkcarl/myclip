#ifndef CLIPMAIN_H
#define CLIPMAIN_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QListWidget>
#include <QFileDialog>

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

    // 创建主要的垂直布局
    QVBoxLayout *mainLayout;

    // 创建一个容器QWidget并设置为主窗口的中心控件
    QWidget *container;

    // 创建视频素材列表和添加视频按钮
    QListWidget *videoListWidget;
    QPushButton *addVideoButton;

    // 创建水平布局用于视频播放和列表,使用QSplitter来允许用户调整两者之间的空间分配
    QSplitter *splitter;

    // 创建水平布局用于按钮
    QHBoxLayout *buttonLayout;

private slots:
    // 自定义playPauseButton的槽函数
    void togglePlayPause();

    // 自定义addVideo的槽函数
    void addVideo();

    // 自定义selectVideo的槽函数
    void selectVideo(const QModelIndex &index);

};
#endif // CLIPMAIN_H
