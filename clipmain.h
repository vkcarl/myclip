#ifndef CLIPMAIN_H
#define CLIPMAIN_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QListWidget>
#include <QFileDialog>
#include <QLabel>

#include "playslider.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClipMain; }
QT_END_NAMESPACE

class PlayerSlider;
class ClipMain : public QMainWindow
{
    Q_OBJECT

public:
    ClipMain(QWidget *parent = nullptr);
    ~ClipMain();

private:
    Ui::ClipMain *ui;

    // 创建视频播放器和视频显示控件,音频输出源
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QAudioOutput *audioOutput;

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

    // 创建用于控制视频播放时刻的进度条和表示播放时间的标签
    PlayerSlider *playSlider;
    QLabel *currentTimeLabel;
    QLabel *totalTimeLabel;
    // 创建用于控制音频音量的滑动条
    QSlider *volumeSlider;

    // 创建视频预览和视频相关控件的垂直布局
    QVBoxLayout *videoLayout;
    QWidget *videoContainer;

    // 创建水平布局用于进度条和播放时间
    QHBoxLayout *sliderLayout;

private slots:
    // 自定义playPauseButton的槽函数
    void togglePlayPause();

    // 自定义addVideo的槽函数
    void addVideo();

    // 自定义selectVideo的槽函数
    void selectVideo(const QModelIndex &index);

    // 自定义滑动条的手动滑动的槽函数
    void setVideoPosition(qint64 position);

    // 设置滑动条随视频播放更新滑动条状态的函数
    void updateSliderPosition(qint64 position);
    void updateDurationLabel(qint64 duration);

    // 设置响应视频播放完毕的槽函数
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    void setupUi();

    // 将毫秒转换为 mm:ss 格式的函数
    QString msToTimeFormat(qint64 ms);

    // 更新时间标签的槽函数
    void updateTimeLabels(qint64 position);
};
#endif // CLIPMAIN_H
