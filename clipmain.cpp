#include "clipmain.h"
#include "ui_clipmain.h"


ClipMain::ClipMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClipMain)
{
    ui->setupUi(this);
    setupUi();
}

ClipMain::~ClipMain()
{
    delete ui;
}

void ClipMain::setupUi() {
    setWindowTitle("播放器");
    //    setWindowIcon(QIcon(":/icon/icon.webp"));// 图标
    //    setFixedSize(800,600);//设置固定大小

    player = new QMediaPlayer;
    videoWidget = new QVideoWidget(this);
    audioOutput = new QAudioOutput(this);


    // 将视频、音频输出设置到视频显示控件
    player->setVideoOutput(videoWidget);
    player->setAudioOutput(audioOutput);

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

    playSlider = new PlayerSlider(this);
    playSlider->setEnabled(false);
    currentTimeLabel = new QLabel("0:00:00", this);
    totalTimeLabel = new QLabel("0:00:00", this);

    volumeSlider = new QSlider(Qt::Vertical, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(static_cast<int>(audioOutput->volume() * 100));

    // 连接进度条信号、视频播放进度信号与槽
    connect(playSlider, &PlayerSlider::sigProgress, this, &ClipMain::setVideoPosition);
    connect(player, &QMediaPlayer::positionChanged, this, &ClipMain::updateSliderPosition);
    // 连接音量滑动条信号、视频播放进度信号与槽
//    connect(player, &QMediaPlayer::positionChanged, this, &ClipMain::updateTimeLabels);
    connect(player, &QMediaPlayer::durationChanged, this, &ClipMain::updateDurationLabel);
    connect(volumeSlider, &QSlider::valueChanged, audioOutput, [this](int value) {
        audioOutput->setVolume(value / 100.0f);
    });
    // 连接mediaStatusChanged信号与槽，用于检测视频播放完毕
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &ClipMain::onMediaStatusChanged);


    // 设置布局
    // 创建视频预览和视频相关控件的垂直布局
    sliderLayout = new QHBoxLayout;
    sliderLayout->addWidget(currentTimeLabel, 0);
    sliderLayout->addWidget(playSlider, 1);
    sliderLayout->addWidget(totalTimeLabel, 0);

    videoLayout = new QVBoxLayout;
    videoLayout->addWidget(videoWidget, 1);
    videoLayout->addLayout(sliderLayout, 0);

    videoContainer = new QWidget;
    videoContainer->setLayout(videoLayout);

    // 创建水平布局用于视频播放和列表
    splitter = new QSplitter;
    splitter->addWidget(videoListWidget);
    splitter->addWidget(videoContainer);
    splitter->setStretchFactor(1, 3); // 第二个部件（视频播放器）占更大空间

    // 创建水平布局用于按钮
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addVideoButton);
    buttonLayout->addWidget(playPauseButton);
    buttonLayout->addWidget(volumeSlider);

    // 创建主要的垂直布局
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter, 1); // 视频区域占更大空间
    mainLayout->addLayout(buttonLayout, 0); // 按钮区域占较小空间

    // 创建一个容器QWidget并设置为主窗口的中心控件
    container = new QWidget;
    container->setLayout(mainLayout);
    this->setCentralWidget(container);
}

void ClipMain::togglePlayPause() {
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
        playPauseButton->setText("Play");
    } else {
        // 获取player当前的视频源地址，判断是否为空
        QUrl mediaUrl = player->source();
        QString mediaPath = mediaUrl.isLocalFile() ? mediaUrl.toLocalFile() : mediaUrl.toString();
        if(mediaPath == nullptr)
            return;
        player->play();
        playPauseButton->setText("Pause");
//        playSlider->setRange(0, player->duration() / 1000);
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
    player->play(); // 开始播放
    player->setPosition(0); // 将播放位置重置为开始
    player->pause(); // 立即暂停，使得播放器停在第一帧
    playSlider->setRange(0, player->duration());
    playPauseButton->setText("Play");
    playSlider->setEnabled(true);
}

void ClipMain::setVideoPosition(qint64 position) {
    player->setPosition(position); // 将秒转换为毫秒
}

void ClipMain::updateSliderPosition(qint64 position) {
    playSlider->setProgress(position); // 将毫秒转换为秒
    updateTimeLabels(position);
}

// 更新时间标签的槽函数
void ClipMain::updateTimeLabels(qint64 position) {
    currentTimeLabel->setText(msToTimeFormat(position));
//    totalTimeLabel->setText(msToTimeFormat(player->duration()));
}

void ClipMain::updateDurationLabel(qint64 duration) {
    totalTimeLabel->setText(msToTimeFormat(duration));
//    playSlider->setRange(0, player->duration() / 1000);
}

// 将毫秒转换为 mm:ss 格式的函数
QString ClipMain::msToTimeFormat(qint64 ms) {
    int seconds = (ms / 1000) % 60;
    int minutes = (ms / (1000 * 60)) % 60;
    int hours = (ms / (1000 * 60 * 60)) % 60;
    return QString::asprintf("%01d:%02d:%02d", hours, minutes, seconds);
}

void ClipMain::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        player->setPosition(0);  // 将播放位置重置为开始
        player->pause();
        playPauseButton->setText("Play");
    }
}
