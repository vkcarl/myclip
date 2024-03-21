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
#include <QListWidgetItem>
#include <QPixmap>
#include <QFileDialog>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtQuickWidgets/QQuickWidget>
#include "graphics/videoitem.h"
#include "utils/commands.h"
#include "graphics/graphicswidgettimeline.h"
#include "graphics/graphicsscene.h"
#include "graphics/graphicswidgetcomposition.h"


#include "track.h"
#include "playslider.h"

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "libavfilter/avfilter.h"
#include "libavfilter/buffersrc.h"
#include "libavfilter/buffersink.h"
#include "libavutil/bprint.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class ClipMain; }
QT_END_NAMESPACE

class PlayerSlider;
class MediaTrackItem;
class ImprovedSplitter;
class QToolBar;
class WidgetTrackDetailsTimeline;
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
    QWidget *buttonWidget;
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

    // 创建一个轨道Item
    MediaTrackItem *mediaTrackItem;
    // 创建垂直布局用于分隔轨道、时间轴和视频、素材栏为上下两部分
    QSplitter *trackSplitter;
    QWidget *trackWidget;

    // 创建一个quickView Widget
    QQuickWidget quickView;

    VideoBlock *videoItems;

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

    // 使用FFmpeg提取视频的缩略图
//    int extractThumbnail(const QString &videoPath, QPixmap **vedioPixmap);

//    int save_rgb_to_file(AVFrame *frame, const char *name);

public:
    void add_track_details(AbstractWidgetTrackDetails* track_details, int index);
    void delete_track_details(AbstractWidgetTrackDetails* track_details);

    qint32 track_details_count() const;
    AbstractWidgetTrackDetails* track_details(int trackIndex) const;

    void buildUI();
protected:
    bool eventFilter(QObject *watched, QEvent *event);

public slots:
    void slot_add_segment_request();
    void slot_delete_segment_request();
    void slot_add_track_request(eSequenceType type);
    void slot_track_menu_triggered(int actionType);

    void slot_delete_track_request(int track_index);
    void slot_delete_track_request(const QUuid& id);
    void slot_splitter_size_changed(int ,int);

    void slot_push_command(QUndoCommand *command){undo_stack_->push(command);}
private:
    qint32 lastTrackIndex(eSequenceType type);
    qint32 lastTrackLocalIndex(eSequenceType type); // set video 0, video 1...
    void createLayout();
    void createStyle();
private:

    WidgetTrackDetailsTimeline* timeline_details_;
    /// timeline with measure
    GraphicsViewScalable*   timeline_view_;
    GraphicsSceneTimeline*  timeline_scene_;
    GraphicsWidgetTimeline* timeline_;

    // place segment -> sequence -> resource(without timeline)
    GraphicsViewScalable*     composition_view_; // VIEW
    GraphicsSceneComposition* composition_scene_; // SCENE
    GraphicsWidgetComposition* composition_graphics_;// ITEM

    // place track details widget
    QScrollArea* track_details_area;
    QSplitter* outer_splitter_;
    QSplitter* inner_l_splitter_; // timeline + tracks track details.
    QSplitter* inner_r_splitter_; // timeline + tracks view
    ImprovedSplitter *track_splitter_; // split track details and timeline track
    QUndoStack* undo_stack_;
};

class ImprovedSplitter : public QSplitter
{
    Q_OBJECT
public:
    ImprovedSplitter(QWidget* parent = nullptr);
    ImprovedSplitter(Qt::Orientation orientation, QWidget *parent = nullptr);
    virtual ~ImprovedSplitter(){}
    void addWidget(QWidget *widget);
    void insertWidget(int index, QWidget* widget);
    qint32 count() const{return QSplitter::count() - 1;}
protected:
    virtual void childEvent(QChildEvent *event);
private slots:
    void slot_splitter_moved(int pos, int index);
private:
    Q_DISABLE_COPY(ImprovedSplitter)

    QWidget*    dummy_widget_;
    QList<int>	old_splitter_size_;
};
#endif // CLIPMAIN_H


