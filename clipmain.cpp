#include "clipmain.h"
#include "ui_clipmain.h"

ClipMain::ClipMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClipMain)
{
    ui->setupUi(this);
    setWindowTitle("播放器");
//    setWindowIcon(QIcon(":/icon/icon.webp"));// 图标
//    setFixedSize(800,600);//设置固定大小

    player = new QMediaPlayer;
    videoWidget = new QVideoWidget(this);

    // 将视频输出设置到视频显示控件
    player->setVideoOutput(videoWidget);

    // 创建开始和暂停按钮
    playPauseButton = new QPushButton("Play");

    // 连接按钮的信号与槽
    QObject::connect(playPauseButton, &QPushButton::clicked, this, &ClipMain::togglePlayPause);

    // 创建视频素材列表和添加视频按钮
    videoListWidget = new QListWidget;
    addVideoButton = new QPushButton("Add Video");

    // 连接按钮的信号与槽
    connect(addVideoButton, &QPushButton::clicked, this, &ClipMain::addVideo);

    // 连接列表选择信号与槽
    connect(videoListWidget, &QListWidget::clicked, this, &ClipMain::selectVideo);


    // 设置布局
    // 创建水平布局用于视频播放和列表
    splitter = new QSplitter;
    splitter->addWidget(videoListWidget);
    splitter->addWidget(videoWidget);
    splitter->setStretchFactor(1, 3); // 第二个部件（视频播放器）占更大空间

    // 创建水平布局用于按钮
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addVideoButton);
    buttonLayout->addWidget(playPauseButton);

    // 创建主要的垂直布局
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter, 1); // 视频区域占更大空间
    mainLayout->addLayout(buttonLayout, 0); // 按钮区域占较小空间

    // 创建一个容器QWidget并设置为主窗口的中心控件
    container = new QWidget;
    container->setLayout(mainLayout);
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

// 自定义addVideo的槽函数
void ClipMain::addVideo() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Video File", "", "Video Files (*.mp4 *.avi *.flv)");
    if (!fileName.isEmpty()) {
        videoListWidget->addItem(fileName);
    }
}

// 自定义selectVideo的槽函数
void ClipMain::selectVideo(const QModelIndex &index) {
    QString fileName = videoListWidget->item(index.row())->text();
    player->setSource(QUrl::fromLocalFile(fileName));
}

