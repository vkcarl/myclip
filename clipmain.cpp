#include <QScrollBar>
#include <QMenu>

#include "clipmain.h"
//#include "qqmlengine.h"
#include "ui_clipmain.h"
#include "videoplaywidget.h"

#include "widget/widgettrackdetails.h"
#include "graphics/graphicswidgetsequence.h"
#include "graphics/graphicswidgetresources.h"



ClipMain::ClipMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClipMain)
{
    ui->setupUi(this);
    undo_stack_ = new QUndoStack(this);
    setupUi();
    buildUI();
    createStyle();

//    ui->setupUi(this);
//    widget_composition_ = new ClipMain;
//    this->setCentralWidget(widget_composition_);
//    this->setWindowTitle("IMF Composition");
}

ClipMain::~ClipMain()
{
    delete ui;
}

void ClipMain::setupUi() {
    setWindowTitle("播放器");
    //    setWindowIcon(QIcon(":/icon/icon.webp"));// 图标
    //    setFixedSize(800,600);//设置固定大小


    // 创建开始和暂停按钮
    playPauseButton = new QPushButton("Play");

    // 连接按钮的信号与槽
    QObject::connect(playPauseButton, &QPushButton::clicked, this, &ClipMain::togglePlayPause);

    // 创建视频素材列表和添加视频按钮
    videoListWidget = new QListWidget;
    videoListWidget->setIconSize(QSize(160, 90));
    addVideoButton = new QPushButton("Add Video");

    // 连接按钮的信号与槽
    connect(addVideoButton, &QPushButton::clicked, this, &ClipMain::addVideo);

    // 连接列表选择信号与槽
    connect(videoListWidget, &QListWidget::clicked, this, &ClipMain::selectVideo);

    playSlider = new PlayerSlider(this);
    playSlider->setEnabled(false);
    currentTimeLabel = new QLabel("0:00:00", this);
    totalTimeLabel = new QLabel("0:00:00", this);

    player = new QMediaPlayer;
    videoWidget = new VideoPlayWidget(player, playPauseButton, playSlider, this);
    audioOutput = new QAudioOutput(this);

    volumeSlider = new QSlider(Qt::Vertical, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(static_cast<int>(audioOutput->volume() * 100));

    // 将视频、音频输出设置到视频显示控件
    player->setVideoOutput(videoWidget);
    player->setAudioOutput(audioOutput);


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

    // 初始化轨道Widget
    trackWidget = new QWidget();
    QGraphicsView *view = new QGraphicsView(trackWidget);
    QGraphicsScene *scene = new QGraphicsScene(view);
    scene->setSceneRect(0, 0, 800, 200);
    videoItems =  new VideoBlock;


    mediaTrackItem = new MediaTrackItem("D:/x90pro/video_20231025_080523.mp4", 100);
    MediaTrackItem* item = new MediaTrackItem("D:/x90pro/2023-10-29 13-32-14.mkv", 100);
    videoItems->AddVideoItem(mediaTrackItem);
    videoItems->AddVideoItem(item);
    videoItems->PutVideoItem2Scene(scene);
//    scene->addItem(mediaTrackItem);
//    mediaTrackItem->setPos(10,10);
    view->setScene(scene);

    // 设置quickView的qml对象
//    QDir importPath = QmlUtilities::qmlDir();
//    engine()->addImportPath(importPath.path());
//    quickView->engine()->addImportPath(importPath.path());

//    quickView.engine()->addImportPath(QStringLiteral("qrc:/"));
//    quickView.setSource(QUrl(QStringLiteral("qrc:/timeline.qml")));
//    QUrl tmp = quickView.source();

    outer_splitter_ = new QSplitter(Qt::Horizontal, this);
    outer_splitter_->setHandleWidth(0);
    outer_splitter_->setChildrenCollapsible(false);

    inner_l_splitter_ = new QSplitter(Qt::Vertical, this);
    inner_l_splitter_->setHandleWidth(2);
    inner_l_splitter_->setChildrenCollapsible(false);

    inner_r_splitter_ = new QSplitter(Qt::Vertical, this);
    inner_r_splitter_->setHandleWidth(2);
    inner_r_splitter_->setChildrenCollapsible(false);

    timeline_view_ = new GraphicsViewScalable(this);
    timeline_scene_ = new GraphicsSceneTimeline(EditRate::EditRate24, this);
    timeline_view_->setScene(timeline_scene_);
    timeline_ = timeline_scene_->timeline();

    timeline_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    timeline_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    timeline_view_->installEventFilter(this);
    timeline_view_->viewport()->installEventFilter(this);

    composition_scene_ =  new GraphicsSceneComposition();
    composition_view_ = new GraphicsViewScalable(this);
    composition_view_->setScene(composition_scene_);
    composition_view_->setFrameShape(QFrame::NoFrame);
    composition_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    composition_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    composition_view_->viewport()->installEventFilter(this);

    track_details_area = new QScrollArea(this);
    track_details_area->setWidgetResizable(true);
    track_details_area->setFrameShape(QFrame::NoFrame);
    track_details_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    track_details_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    track_details_area->viewport()->installEventFilter(this);


    timeline_details_ = new WidgetTrackDetailsTimeline(this);

    inner_l_splitter_->addWidget(timeline_details_);
    inner_l_splitter_->addWidget(track_details_area);

    inner_r_splitter_->addWidget(timeline_view_);
    inner_r_splitter_->addWidget(composition_view_);
    outer_splitter_->addWidget(inner_l_splitter_);
    outer_splitter_->addWidget(inner_r_splitter_);
    outer_splitter_->setStretchFactor(0, 0);
    outer_splitter_->setStretchFactor(1, 2);
    outer_splitter_->setStretchFactor(2, 1);

    track_splitter_ = new ImprovedSplitter(Qt::Vertical); //track details container
    track_splitter_->setHandleWidth(0); // handle is a indicator than can resize the widget in the spliter
    track_splitter_->setChildrenCollapsible(false);
    track_details_area->setWidget(track_splitter_);

    // resize splitters size
    QList<int> splitter_sizes;
    splitter_sizes << HEIGHT_TIMELINE_WIDGET << -1;
    //splitter_sizes << timeline_view_->minimumSizeHint().height() << -1;
    //Keep the timeline view size with timeline track details.
    timeline_view_->setMinimumSize(timeline_details_->minimumSizeHint());
    inner_r_splitter_->setStretchFactor(1, 1);
    inner_l_splitter_->setStretchFactor(1, 1);
    inner_r_splitter_->setSizes(splitter_sizes);
    inner_l_splitter_->setSizes(splitter_sizes);

    // 剪辑轨道和时间轴部分的信号连接
    connect(inner_l_splitter_, &QSplitter::splitterMoved, this, &ClipMain::slot_splitter_size_changed);connect(inner_r_splitter_, &QSplitter::splitterMoved, this, &ClipMain::slot_splitter_size_changed);
    /* 同步 indicator image and indicator line. */
    connect(timeline_scene_->frameIndicator(), &GraphicsObjectVerticalIndicator::sig_xPos_changed, composition_scene_->frameIndicator(), &GraphicsObjectVerticalIndicator::slot_set_xPos);
    connect(timeline_scene_, &GraphicsSceneTimeline::sig_current_frame_changed, timeline_details_, &WidgetTrackDetailsTimeline::slot_set_timecode);
    connect(timeline_scene_, &GraphicsSceneTimeline::sig_push_command, this, &ClipMain::slot_push_command);
    connect(composition_view_->horizontalScrollBar(), &QScrollBar::valueChanged, timeline_view_->horizontalScrollBar(), &QScrollBar::setValue);
    connect(timeline_details_, &WidgetTrackDetailsTimeline::sig_height_about_to_change, timeline_, &GraphicsWidgetTimeline::setHeight);
    connect(timeline_details_, &WidgetTrackDetailsTimeline::sig_frame_timecode_toggled, timeline_, &GraphicsWidgetTimeline::slot_show_frames_toggled);


    // 设置跟时间轴、轨道无关的布局
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
    buttonWidget = new QWidget();
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addVideoButton);
    buttonLayout->addWidget(playPauseButton);
    buttonLayout->addWidget(volumeSlider);
    buttonWidget->setLayout(buttonLayout);

    // 创建视素材、预览到按钮到轨道时间轴垂直排列的splitter
    trackSplitter = new QSplitter(Qt::Vertical);
    trackSplitter->addWidget(splitter);
    trackSplitter->addWidget(buttonWidget);
    trackSplitter->addWidget(trackWidget);
    trackSplitter->setStretchFactor(0, 4);
    trackSplitter->setStretchFactor(1, 1);
    trackSplitter->setStretchFactor(2, 1);

    // 创建主要的垂直布局
    mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(trackSplitter);
    //    layout->setMargin(0);
    // function setMargin(int) has been deprecated, use setContentsMargins(int, int, int, int) instead.
    // 它其实是一个调整布局边距的值的方法，四个参数依次分别是左、上、右、下边距值。
    mainLayout->addWidget(outer_splitter_);

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
//    QString fileName = QFileDialog::getOpenFileName(this, "Open Video File", "", "Video Files (*.mp4 *.avi *.flv)");
//    if (!fileName.isEmpty()) {
////        videoListWidget->addItem(fileName);
//        QPixmap *thumbnail;
//        // 提取缩略图
//        if(extractThumbnail(fileName, &thumbnail) != 0)
//        {
//            return;
//        }
//        QIcon thumbnailIcon(*thumbnail);
//        delete(thumbnail);
//        QListWidgetItem *item = new QListWidgetItem;
//        item->setIcon(thumbnailIcon);
//        item->setText(fileName);  // 可以选择设置文本，或者留空

//        videoListWidget->addItem(item);
//    }
}

// 自定义selectVideo的槽函数
void ClipMain::selectVideo(const QModelIndex &index) {
    QString fileName = videoListWidget->item(index.row())->text();
    player->setSource(QUrl::fromLocalFile(fileName));
    player->play(); // 开始播放
    player->setPosition(0); // 将播放位置重置为开始
    player->pause(); // 立即暂停，使得播放器停在第一帧
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
//    qint64 duration2 = player->duration();
    playSlider->setRange(0, player->duration());
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

void ClipMain::createLayout()
{

    connect(inner_l_splitter_, &QSplitter::splitterMoved, this, &ClipMain::slot_splitter_size_changed);connect(inner_r_splitter_, &QSplitter::splitterMoved, this, &ClipMain::slot_splitter_size_changed);
    /* 同步 indicator image and indicator line. */
    connect(timeline_scene_->frameIndicator(), &GraphicsObjectVerticalIndicator::sig_xPos_changed, composition_scene_->frameIndicator(), &GraphicsObjectVerticalIndicator::slot_set_xPos);
    connect(timeline_scene_, &GraphicsSceneTimeline::sig_current_frame_changed, timeline_details_, &WidgetTrackDetailsTimeline::slot_set_timecode);
    connect(timeline_scene_, &GraphicsSceneTimeline::sig_push_command, this, &ClipMain::slot_push_command);
    connect(composition_view_->horizontalScrollBar(), &QScrollBar::valueChanged, timeline_view_->horizontalScrollBar(), &QScrollBar::setValue);
    connect(timeline_details_, &WidgetTrackDetailsTimeline::sig_height_about_to_change, timeline_, &GraphicsWidgetTimeline::setHeight);
    connect(timeline_details_, &WidgetTrackDetailsTimeline::sig_frame_timecode_toggled, timeline_, &GraphicsWidgetTimeline::slot_show_frames_toggled);
}

void ClipMain::createStyle() {

    timeline_view_->setObjectName("TimelineView");
    timeline_view_->setStyleSheet(QString(
                                      "QFrame#%1 {"
                                      "background-color: %2;"
                                      "border-width: 1px;"
                                      "border-top-width: 0px;"
                                      "border-right-width: 0px;"
                                      "border-left-width: 0px;"
                                      "border-color: %3;"
                                      "border-style: solid;"
                                      "border-radius: 0px;"
                                      "}").arg(timeline_view_->objectName()).arg(QColor(CPL_COLOR_BACKGROUND).name()).arg(QColor(CPL_BORDER_COLOR).name()));

    composition_view_->setObjectName("CompositionView");
    composition_view_->setStyleSheet(QString(
                                         "QFrame#%1 {"
                                         "background-color: %2;"
                                         "border-width: 1px;"
                                         "border-bottom-width: 0px;"
                                         "border-right-width: 0px;"
                                         "border-left-width: 0px;"
                                         "border-color: %3;"
                                         "border-style: solid;"
                                         "border-radius: 0px;"
                                         "}").arg(composition_view_->objectName()).arg(QColor(CPL_COLOR_BACKGROUND).name()).arg(QColor(CPL_BORDER_COLOR).name()));

    track_splitter_->setObjectName("TrackSplitter");
    track_splitter_->setStyleSheet(QString(
                                       "QFrame#%1 {"
                                       "border-width: 1px;"
                                       "border-bottom-width: 0px;"
                                       "border-right-width: 0px;"
                                       "border-left-width: 0px;"
                                       "border-color: %3;"
                                       "border-style: solid;"
                                       "border-radius: 0px;"
                                       "}").arg(track_splitter_->objectName()).arg(QColor(CPL_BORDER_COLOR).name()));
}

void ClipMain::buildUI()
{

    GraphicsWidgetSegmentIndicator *p_graphics_segment_indicator = new GraphicsWidgetSegmentIndicator(timeline_);
    composition_graphics_ = composition_scene_->composition();
    slot_add_track_request(MainImageSequence);
    slot_add_track_request(MainAudioSequence);
    slot_add_track_request(MainAudioSequence);
    slot_add_track_request(MainAudioSequence);
    slot_add_track_request(SubtitlesSequence);
}

bool ClipMain::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Wheel)
    {
        if(watched == timeline_view_->viewport())
        {
            QWheelEvent* e = static_cast<QWheelEvent*>(event);
            qreal factor = pow(1.2, e->angleDelta().y() / 240.0);
            eScaleStatus scaleResut = composition_view_->scaleView(factor);
            if( ScaleNormal == scaleResut)
            {
                timeline_view_->scaleView(factor);
                timeline_view_->horizontalScrollBar()->setValue(composition_view_->horizontalScrollBar()->value());
            }
            else
            {
                timeline_view_->setTransform(composition_view_->transform());
                if(scaleResut == ScaleMin)
                {
                    composition_view_->horizontalScrollBar()->setValue(0);
                }
            }
            return true;
        } // sync track details and tracks
        else if(watched == composition_view_->viewport() || watched == track_details_area->viewport())
        {
            QWheelEvent *wheel_event = dynamic_cast<QWheelEvent*>(event);
            int delta = -wheel_event->angleDelta().y();
            if(watched == composition_view_->viewport())
            {
                composition_view_->verticalScrollBar()->setValue(composition_view_->verticalScrollBar()->value() + delta);
                track_details_area->verticalScrollBar()->setValue(composition_view_->verticalScrollBar()->value() + delta);
            }
            else if(watched == track_details_area->viewport())
            {
                track_details_area->verticalScrollBar()->setValue(composition_view_->verticalScrollBar()->value() + delta);
                composition_view_->verticalScrollBar()->setValue(track_details_area->verticalScrollBar()->value() + delta);
            }
            return true;
        }
    }
}

qint32 ClipMain::lastTrackLocalIndex(eSequenceType type)
{
    int index = 0;
    for(int i = 0; i < track_splitter_->count(); i++)
    {
        AbstractWidgetTrackDetails* track = qobject_cast<AbstractWidgetTrackDetails*>(track_splitter_->widget(i));
        {
            if(track != nullptr && track->type() == type)
                index++;
        }
    }
    return index;
}

qint32 ClipMain::lastTrackIndex(eSequenceType type)
{
    int index = -1;
    for(int i = 0; i < track_splitter_->count(); i++)
    {
        AbstractWidgetTrackDetails* track = qobject_cast<AbstractWidgetTrackDetails*>(track_splitter_->widget(i));
        {
            if(track != nullptr && track->type() == type)
                index = i;
        }
    }
    return index;
}

AbstractWidgetTrackDetails* ClipMain::track_details(int trackIndex) const
{
    return qobject_cast<AbstractWidgetTrackDetails*>(track_splitter_->widget(trackIndex));
}

void ClipMain::slot_delete_segment_request()
{
    GraphicsWidgetSegment *segment = composition_graphics_->segment();
    composition_graphics_->delete_segment(segment);

}

void ClipMain::slot_add_segment_request()
{
    QUndoCommand *root = new QUndoCommand(nullptr);
    QUuid uuid(QUuid::createUuid());
    GraphicsWidgetSegment *new_segment = new GraphicsWidgetSegment(composition_graphics_, uuid);
    GraphicsWidgetSegmentIndicator *segment_indicator = new GraphicsWidgetSegmentIndicator(timeline_);

    for(int i = 0; i < track_details_count(); i++) {
        AbstractWidgetTrackDetails *p = track_details(i);
        GraphicsWidgetSequence *new_sequence = new GraphicsWidgetSequence(new_segment, track_details(i)->type(), track_details(i)->track_id());
        new_sequence->setHeight(track_details(i)->height());
        AddSequenceCommand *p_add_sequence = new AddSequenceCommand(new_sequence, i, new_segment, root);
    }
    // qint64 total_duration = this->GetTotalDuration();
    //  total_duration = (total_duration >= 600 ? total_duration : 600);
    new_segment->setDuration(5000 / 5);  // Set duration of new segment to 20% of the total CPL duration	mpCompositionGraphicsWidget->layout()->activate();
    timeline_->layout()->activate();
}

void ClipMain::add_track_details(AbstractWidgetTrackDetails *track_details, int index)
{
    eSequenceType sequence_type = track_details->type();
    if(sequence_type == MainImageSequence)
    {
        track_splitter_->insertWidget(index, track_details);
    }
    else if(sequence_type == MainAudioSequence)
    {
        track_splitter_->insertWidget(index, track_details);
    }
    else if(sequence_type == SubtitlesSequence)
    {
        track_splitter_->insertWidget(index, track_details);
    }
}

void ClipMain::delete_track_details(AbstractWidgetTrackDetails *track_details)
{
    track_details->setParent(nullptr);
}

void ClipMain::slot_delete_track_request(int track_index)
{

}

qint32 ClipMain::track_details_count() const
{
    return track_splitter_->count() >= 0 ? track_splitter_->count() : 0;
}

void ClipMain::slot_delete_track_request(const QUuid& id)
{

}
// to resize the boundary of timeline and track widget.
// not include between in the widget list.
// resize track widget should: track widget should link to the sequence.
void ClipMain::slot_splitter_size_changed(int, int)
{
    QSplitter* sp = qobject_cast<QSplitter*>(sender());
    if(sp != nullptr)
    {
        if(sp == inner_l_splitter_)
            inner_r_splitter_->setSizes(inner_l_splitter_->sizes());
        else if(sp == inner_r_splitter_)
            inner_l_splitter_->setSizes(inner_r_splitter_->sizes());
    }
}

void ClipMain::slot_track_menu_triggered(int actionType)
{
    WidgetTrackDetails* track = qobject_cast<WidgetTrackDetails*>(sender());
    if(track != nullptr)
    {
        eSequenceType type = track->type();
        switch (actionType) {
        case WidgetTrackDetails::ActionInsert:
            slot_add_track_request(type);
            break;
        case WidgetTrackDetails::ActionDelete:
            slot_delete_track_request(0);
            break;
        default:
            break;
        }
    }
}

/* Add track == Add track details + add track. */
void ClipMain::slot_add_track_request(eSequenceType type)
{
    QUuid track_id(QUuid::createUuid());
    QUndoCommand* root = new QUndoCommand(nullptr);
    int track_order = lastTrackLocalIndex(type);
    WidgetTrackDetails* track = new WidgetTrackDetails(track_id,track_order, type, this);
    int insert_index = lastTrackIndex(type) + 1; // pos where should insert.
    if(insert_index == 0)
    {
        insert_index = track_splitter_->count();
    }

    GraphicsWidgetSegment* segment = composition_graphics_->segment();
    GraphicsWidgetSequence* sequence = nullptr;
    if(segment)
    {
        sequence = new GraphicsWidgetSequence(segment, type, track_id);
        AddSequenceCommand* command_add_sequence = new AddSequenceCommand(sequence, insert_index, segment, root);
        AbstractGraphicsWidgetResources* resource = nullptr;
        switch(type)
        {
        case MainImageSequence:
            resource = new GraphicsWidgetVideoResource(sequence);
            break;
        case MainAudioSequence:
            resource = new GraphicsWidgetAudioResource(sequence);
            break;
        case SubtitlesSequence:
            resource = new GraphicsWidgetTimedTextResource(sequence);
            break;
        }
        AddResourceCommand* command_add_resource = new AddResourceCommand(sequence, resource, sequence->resourceCount(), root);
    }
    AddTrackDetailsCommand *command_add_track_details = new AddTrackDetailsCommand(track, this, insert_index, root);
    connect(track, &WidgetTrackDetails::sig_height_about_to_change, sequence, &GraphicsWidgetSequence::setHeight);
    connect(track, &WidgetTrackDetails::sig_track_action_triggered, this, &ClipMain::slot_track_menu_triggered);
    undo_stack_->push(root);
}

ImprovedSplitter::ImprovedSplitter(QWidget *parent) :
    QSplitter(parent){

    dummy_widget_ = new QWidget(this);
    addWidget(dummy_widget_);
    setStretchFactor(indexOf(dummy_widget_), 999);
    connect(this, SIGNAL(splitterMoved(int, int)), this, SLOT(slot_splitter_moved(int,int)));
    refresh();
    old_splitter_size_ = sizes();
}

ImprovedSplitter::ImprovedSplitter(Qt::Orientation orientation, QWidget *parent /*= nullptr*/) :
    QSplitter(orientation, parent), dummy_widget_(nullptr) {

    dummy_widget_ = new QWidget(this);
    addWidget(dummy_widget_);
    setStretchFactor(indexOf(dummy_widget_), 999);
    connect(this, SIGNAL(splitterMoved(int, int)), this, SLOT(slot_splitter_moved(int,int)));
    refresh();
    if(parentWidget())
        setFixedHeight(parentWidget()->height());
    old_splitter_size_ = sizes();
}

void ImprovedSplitter::addWidget(QWidget *widget)
{
    QSplitter::addWidget(widget);
    QSplitter::addWidget(dummy_widget_);
    QSplitterHandle *p_handle = handle(indexOf(widget));
    if(p_handle)
        p_handle->installEventFilter(this);
    refresh();
    old_splitter_size_ = sizes();
}

void ImprovedSplitter::insertWidget(int index, QWidget *widget) {

    QSplitter::insertWidget(index, widget);
    QSplitter::addWidget(dummy_widget_);
    QSplitterHandle *p_handle = handle(indexOf(widget));
    if(p_handle)
        p_handle->installEventFilter(this);
    refresh();
    old_splitter_size_ = sizes();
}

void ImprovedSplitter::childEvent(QChildEvent *pEvent)
{
    QSplitter::childEvent(pEvent);
    if(pEvent->child()->isWidgetType()) {
        QWidget *p_widget = static_cast<QWidget *>(pEvent->child());
        if(p_widget->isWindow()) return;
        if(pEvent->type() == QEvent::ChildRemoved) {
            old_splitter_size_ = sizes();
            old_splitter_size_.removeAt(indexOf(p_widget));
            int sum = 0;
            for(int i = 0; i < old_splitter_size_.size() - 1; i++) {
                sum += old_splitter_size_.at(i);
            }
            if(parentWidget())setFixedHeight(sum + parentWidget()->height());
        }
    }
}

void ImprovedSplitter::slot_splitter_moved(int pos, int index)
{
    // index should not be <= 0
    if(index > 0)
    {
        old_splitter_size_[index - 1] = sizes().at(index - 1);
        int sum = 0;
        for(int i = 0; i < old_splitter_size_.size() - 1; i++)
        {
            sum += old_splitter_size_.at(i);
        }
        if(parentWidget())
            setFixedHeight(sum + parentWidget()->height());
        setSizes(old_splitter_size_);
    }
}

