#include "clipmain.h"
#include "ui_clipmain.h"

ClipMain::ClipMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClipMain)
{
    ui->setupUi(this);
    setWindowTitle("播放器");
//    setWindowIcon(QIcon(":/icon/icon.webp"));// 图标
    setFixedSize(800,600);//设置固定大小

    player = new QMediaPlayer;
    videoWidget = new QVideoWidget(this);

    // 设置视频文件源
    player->setSource(QUrl::fromLocalFile("../encode/juren-30s.mp4"));

    // 将视频输出设置到视频显示控件
    player->setVideoOutput(videoWidget);

    // 将视频控件设置为主窗口的中心控件
    this->setCentralWidget(videoWidget);

    // 创建开始和暂停按钮
    playPauseButton = new QPushButton("Play");

    // 连接按钮的信号与槽
    QObject::connect(playPauseButton, &QPushButton::clicked, this, &ClipMain::togglePlayPause);

    // 设置布局
    layout = new QVBoxLayout;
    layout->addWidget(videoWidget);
    layout->addWidget(playPauseButton);

    // 创建一个容器QWidget并设置为主窗口的中心控件
    container = new QWidget;
    container->setLayout(layout);
    this->setCentralWidget(container);
}

ClipMain::~ClipMain()
{
    delete ui;
}

void ClipMain::togglePlayPause() {
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
        playPauseButton->setText("Play");
    } else {
        player->play();
        playPauseButton->setText("Pause");
    }
}

