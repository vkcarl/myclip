#ifndef GRAPHICSWIDGETRESOURCES_H
#define GRAPHICSWIDGETRESOURCES_H
#include "graphicscommon.h"
#include "imf/imfpackage.h"
#include "ffmpeg_util/extractduration.h"
#include <QUuid>
#include <QMimeData>
#include <QDrag>
#include <QGraphicsSceneDragDropEvent>
#include <QFileInfo>
#include "utils/FrameRateManager.h"

class GraphicsWidgetSequence;
class AbstractGraphicsWidgetResources;

enum eTrimHandlePos
{
    Left = 0,
    Right
};

class TrimHandle : public QGraphicsItem, public AbstractViewTransformNotifier
{
public:
    TrimHandle(AbstractGraphicsWidgetResources* parent, eTrimHandlePos pos);
    ~TrimHandle(){}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override{return rect_;}

    eTrimHandlePos direction() const{return pos_;}
    void setDirection(eTrimHandlePos p);
    void setHeight(qreal h);
    void setWidth(qreal w);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void ViewTransformEvent(const QTransform &rViewTransform) override;
    virtual QGraphicsView* GetObservableView() const override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private:
    Q_DISABLE_COPY(TrimHandle)

    eTrimHandlePos pos_;
    qint32 mouse_x_offset_;
    bool   is_mouse_pressed_;
    QRectF rect_;
};

class DurationIndicator : public QGraphicsItem
{
public:
    DurationIndicator(AbstractGraphicsWidgetResources* parent);
    virtual ~DurationIndicator(){}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override{return rect_;}
    void setRect(const QRectF& rect){prepareGeometryChange(); rect_ = rect;}
private:
    Q_DISABLE_COPY(DurationIndicator)
    QRectF rect_;
};

class AbstractGraphicsWidgetResources : public GraphicsWidgetBase
{
    Q_OBJECT
public:
    AbstractGraphicsWidgetResources(GraphicsWidgetSequence* parent, const QColor& color);
    virtual ~AbstractGraphicsWidgetResources(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
//    QRectF boundingRect() const override;
    QUuid id() const{return id_;}

    QColor color() const{return color_;}
    void   setColor(const QColor& color){color_ = color; update();}

    QString  annotation() const{return asset_->annotation_;}
    qint32   repeatCount() const{return 1;}
    Duration entryPoint() const{return 0;}
    Duration sourceDuration() const{ return asset_->source_duration_; }
    Duration intrinsicDuration() const{return asset_->source_duration_;}
    EditRate editRate() const{return edit_rate_;}

    void setAnnotation(const QString& annotation){asset_->annotation_ = (annotation);}
    void setEntryPoint(const Duration& d);
    void setSourceDuration(const Duration& d);

    //! Transforms a local Timecode to an absolute Cpl timecode.
    Timecode MapToCplTimeline(const Timecode &rLocalTimecode) const;
    //! Transforms a local Duration to Cpl Duration (replaces Resource Edit Rate with Cpl Edit Rate).
    Duration MapToCplTimeline(const Duration &rLocalDuration) const;
    virtual void trimHandleInUse(eTrimHandlePos pos, bool active);
    virtual void TrimHandleMoved(eTrimHandlePos pos) {}

    void trimResource(qint32 pos, qint32 lastPos, eTrimHandlePos epos);

    void maximizeZValue();
    void restoreZValue();
    GraphicsWidgetSequence* getSequence() const;
    // QSharedPointer<AssetMxfTrack> asset_mxf_;
signals:
    void sourceDurationChanged(const Duration& old_duration, const Duration& new_duration);
    void entryPointChanged(const Duration& old_entry_point, const Duration& new_entry_point);
protected:

    virtual void resizeEvent(QGraphicsSceneResizeEvent* e) override;
    virtual void hideEvent(QHideEvent* e) override;
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* e) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;
    virtual bool extendGrid(QPointF &point, eGridPosition which) const override;
    virtual double samplesPerFrame(const EditRate& compositionEditRate) const{return 1;}
    virtual void CPLEditRateChanged(){updateGeometry();}

    AssetMxfTrack* asset_;
    QSharedPointer<AssetMxfTrack> mAssset;
    EditRate edit_rate_;
private:
    Q_DISABLE_COPY(AbstractGraphicsWidgetResources)
    QUuid id_;
    QColor color_;
    Duration old_entry_point_;
    Duration old_source_duration_;
    TrimHandle* left_trim_handle_;
    TrimHandle* right_trim_handle_;
    DurationIndicator* duration_indicator_;
    GraphicsObjectVerticalIndicator* vertical_indicator_;

};

class GraphicsWidgetFileResource : public AbstractGraphicsWidgetResources
{
    Q_OBJECT
public:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
        if (event->mimeData()->hasFormat("text/plain")) {
            event->acceptProposedAction();
        }
    }

    void dragMoveEvent(QGraphicsSceneDragDropEvent* event) {
        // 通常你也想在这里接受动作，以便在拖动时给予用户反馈
        event->acceptProposedAction();
    }

    void dropEvent(QGraphicsSceneDragDropEvent *event) {
        // 获取视频路径
        QString filePath = event->mimeData()->text();

        // 根据视频时长和时间轴的刻度创建一个表示视频的长条
        // ...
        int64_t duration;
        double fps;
        int err;
        if(err = MediaDurationTool::extractDuration(filePath, &duration, &fps)) {
            qDebug() << "error occurs in extractDuration function";
            return;
        }
        asset_->source_duration_ = duration;
        asset_->intrinsic_duration_ = duration;
        asset_->source_file_ = QFileInfo(filePath);
        QStringList frame_rate_name_list_ = EditRate::GetFrameRateNames();
        bool ok;

        for(QString& name : frame_rate_name_list_) {
            double frame_rate_candidate_ = name.toDouble(&ok);
            if(!ok) {
                qDebug() << "error occurs in finding suitable EditRate";
                return;
            }
            if(abs(frame_rate_candidate_ - fps) < 0.001) {
                edit_rate_ = EditRate::GetEditRate(name);
                if(edit_rate_ > FrameRateManager::getEditRate()) {
                    FrameRateManager::changeEditRate(edit_rate_);
                }
                break;
            }
        }
    }

    GraphicsWidgetFileResource(GraphicsWidgetSequence *parent, const QColor& color);
    virtual ~GraphicsWidgetFileResource(){}
    virtual int type() const{return GraphicsWidgetFileResourceType;}
private:
    Q_DISABLE_COPY(GraphicsWidgetFileResource)
};

class GraphicsWidgetDummyResource : public GraphicsWidgetFileResource
{
public:
    GraphicsWidgetDummyResource();
    virtual ~GraphicsWidgetDummyResource(){}
private:
    Q_DISABLE_COPY(GraphicsWidgetDummyResource)
};

class GraphicsWidgetVideoResource : public GraphicsWidgetFileResource
{
    Q_OBJECT
public:
    GraphicsWidgetVideoResource(GraphicsWidgetSequence *parent);
    virtual ~GraphicsWidgetVideoResource(){}
    virtual int type() const override{return GraphicsWidgetVideoResourceType;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
protected:
    virtual void trimHandleInUse(eTrimHandlePos pos, bool active) override;
    virtual void cplEditRateChanged(){}
    virtual double samplesPerFrame(const EditRate& compositionEditRate)const override{return 1;}
private slots:
    void slot_entry_point_changed();
    void slot_source_duration_changed();
private:
    Q_DISABLE_COPY(GraphicsWidgetVideoResource)
    QImage left_proxy_image_;
    QImage right_proxy_image_;
    bool   is_trim_active_;
    bool   is_proxy_visible_;
};

class GraphicsWidgetAudioResource : public GraphicsWidgetFileResource
{
public:
    GraphicsWidgetAudioResource(GraphicsWidgetSequence* parent);
    virtual ~GraphicsWidgetAudioResource(){}
    virtual double samplesPerFrame(const EditRate& compositionEditRate)const{return 1;}
private:
    Q_DISABLE_COPY(GraphicsWidgetAudioResource)
};

class GraphicsWidgetTimedTextResource : public GraphicsWidgetFileResource
{
public:
    GraphicsWidgetTimedTextResource(GraphicsWidgetSequence* parent);
    virtual ~GraphicsWidgetTimedTextResource(){}
    virtual double samplesPerFrame(const EditRate& compositionEditRate)const{return 1;}
private:
    Q_DISABLE_COPY(GraphicsWidgetTimedTextResource)
};




#endif // GRAPHICSWIDGETRESOURCES_H
