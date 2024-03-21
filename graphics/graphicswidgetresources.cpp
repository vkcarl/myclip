#include "graphicswidgetresources.h"
#include "graphicswidgetsequence.h"
#include "graphicswidgetsegment.h"
#include "graphicsscene.h"
#include "utils/commands.h"
#include "ffmpeg_util/extractthumbnail.h"

#include <math.h>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
TrimHandle::TrimHandle(AbstractGraphicsWidgetResources *parent, eTrimHandlePos pos)
    :QGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemSendsScenePositionChanges);
    setDirection(pos);
    setWidth(8);
    if(pos_ == Right)
    {
        setTransform(QTransform::fromScale(1 / GetViewTransform().m11(), 1).translate(-boundingRect().width() - 1, 0));
    }
    else
    {
        setTransform(QTransform::fromScale(1 / GetViewTransform().m11(), 1));
    }
}

void TrimHandle::setDirection(eTrimHandlePos p)
{
    pos_ = p;
    QCursor cursor;
    switch (pos_) {
    case Left:
        cursor = QCursor(QPixmap(":/style/cursor_crop_right.png"));
        break;
    case Right:
        cursor = QCursor(QPixmap(":/style/cursor_crop_left.png"));
        break;
    default:
        cursor = QCursor(Qt::SplitHCursor);
        break;
    }
    setCursor(cursor);
}

void TrimHandle::setHeight(qreal h)
{
    prepareGeometryChange();
    rect_.setHeight(h);
}

void TrimHandle::setWidth(qreal width)
{
    qreal old_width = boundingRect().width();
    prepareGeometryChange();
    rect_.setWidth(width);
    if(pos_ == Right)
    {
        setTransform(transform().translate(old_width, 0));
        setTransform(transform().translate(-boundingRect().width(), 0));
    }
}

void TrimHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractGraphicsWidgetResources* source_widget = qobject_cast<AbstractGraphicsWidgetResources*>(parentWidget());
    if(source_widget)
    {
        if(event->button() == Qt::LeftButton)
        {
            mouse_x_offset_ = (qint32)(event->scenePos().x() + 0.5);
            is_mouse_pressed_ = true;
            source_widget->trimHandleInUse(pos_, true);
            source_widget->trimResource(event->scenePos().x() + .5, event->scenePos().x() + .5, pos_);
        }
    }
}

void TrimHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // CT notic: event->button() always retur NoButton in MoveEvent.
    // We should use event->buttons() & Qt::leftButton
    if(!(event->buttons() & Qt::LeftButton))
        return;
    AbstractGraphicsWidgetResources* source_widget = qobject_cast<AbstractGraphicsWidgetResources*>(parentWidget());
    if(source_widget)
    {
         source_widget->trimResource(event->scenePos().x() + .5, event->scenePos().x() + .5, pos_);
    }
}

void TrimHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractGraphicsWidgetResources* source_widget = qobject_cast<AbstractGraphicsWidgetResources*>(parentWidget());
    if(source_widget)
    {
        if(event->button() == Qt::LeftButton)
        {
            is_mouse_pressed_ = false;
            source_widget->trimHandleInUse(pos_, false);
        }
    }
}

QGraphicsView* TrimHandle::GetObservableView() const
{
    if(scene())
    {
        if(scene()->views().size() > 0)
            return scene()->views().first();
    }
    return nullptr;
}

QVariant TrimHandle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSceneHasChanged) {
        ViewTransformEvent(GetViewTransform());
    }
    return QGraphicsItem::itemChange(change, value);
}

void TrimHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF trim_rect(boundingRect());
    trim_rect.adjust(0, 2, 0, -2);
    QColor dark(0, 0, 0, 120);
    QRectF exposed_rect(option->exposedRect);
    if(exposed_rect.left() - 1 >= boundingRect().left())
        exposed_rect.adjust(-1, 0, 0, 0);
    if(exposed_rect.right() + 1 <= boundingRect().right())
        exposed_rect.adjust(0, 0, 1, 0);
    QRectF visible_rect(trim_rect.intersected(exposed_rect));
    if(pos_ == Left)
        visible_rect.setLeft(boundingRect().left() + 3);
    else
        visible_rect.setRight(boundingRect().right() - 3);
    visible_rect.translate(-.5, -.5);
    if(visible_rect.isEmpty() == false) {
        AbstractGraphicsWidgetResources *p_resource_widget = qobject_cast<AbstractGraphicsWidgetResources *>(parentWidget());
        if(p_resource_widget) {
            if(boundingRect().intersects(option->exposedRect) && trim_rect.width() * 2 <= p_resource_widget->boundingRect().width() * GetViewTransform().m11()) {
                painter->fillRect(visible_rect, dark);
            }
        }
    }
}

void TrimHandle::ViewTransformEvent(const QTransform &rTransform) {

    if(pos_ == Right)
        setTransform(QTransform::fromScale(1 / rTransform.m11(), 1).translate(-boundingRect().width() - 1, 0));
    else
        setTransform(QTransform::fromScale(1 / rTransform.m11(), 1));
}

DurationIndicator::DurationIndicator(AbstractGraphicsWidgetResources *parent)
    :QGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemUsesExtendedStyleOption);
}

void DurationIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF exposed_rect(option->exposedRect);
    if(exposed_rect.left() - 1 >= boundingRect().left())
        exposed_rect.adjust(-1, 0, 0, 0);
    if(exposed_rect.right() + 1 <= boundingRect().right())
        exposed_rect.adjust(0, 0, 1, 0);
    QRectF visible_rect(boundingRect().intersected(exposed_rect));
    visible_rect.adjust(0, 0, -1. / painter->transform().m11(), -1. / painter->transform().m22());

    QPen pen;
    pen.setWidth(0);
    painter->setPen(pen);

    pen.setColor(QColor(CPL_COLOR_DURATION_INDICATOR));
    painter->setPen(pen);
    if(exposed_rect.top() <= boundingRect().top())
        painter->drawLine(visible_rect.topLeft(), visible_rect.topRight());
    if(exposed_rect.bottom() >= boundingRect().bottom())
        painter->drawLine(visible_rect.bottomLeft(), visible_rect.bottomRight());
    if(exposed_rect.left() - 1 <= boundingRect().left())
        painter->drawLine(visible_rect.topLeft(), QPointF(visible_rect.left(), visible_rect.top() + 20));
    if(exposed_rect.left() - 1 <= boundingRect().left())
        painter->drawLine(visible_rect.bottomLeft(), QPointF(visible_rect.left(), visible_rect.bottom() - 20));
    if(exposed_rect.right() + 1 >= boundingRect().right())
        painter->drawLine(visible_rect.topRight(), QPointF(visible_rect.right(), visible_rect.top() + 20));
    if(exposed_rect.right() + 1 >= boundingRect().right())
        painter->drawLine(visible_rect.bottomRight(), QPointF(visible_rect.right(), visible_rect.bottom() - 20));
}

AbstractGraphicsWidgetResources::AbstractGraphicsWidgetResources(GraphicsWidgetSequence *parent, const QColor& color)
    :GraphicsWidgetBase(parent), color_(color)
{
    left_trim_handle_ = new TrimHandle(this, Left);
    right_trim_handle_ = new TrimHandle(this, Right);
    duration_indicator_ = new DurationIndicator(this);
    vertical_indicator_ = new GraphicsObjectVerticalIndicator(1, 0, QColor(CPL_COLOR_DEFAULT_SNAP_INDICATOR), this);
    vertical_indicator_->hideHead();
    left_trim_handle_->hide();
    right_trim_handle_->hide();
    duration_indicator_->hide();
    vertical_indicator_->hide();
//    old_source_duration_ = 1000; // fixed value for test.
    asset_ = new AssetMxfTrack;
//    asset_->source_duration_ = 1000;
//    asset_->intrinsic_duration_ = 1000;

    setAcceptDrops(true);
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemUsesExtendedStyleOption | QGraphicsItem::ItemIsSelectable);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

//QRectF AbstractGraphicsWidgetResources::boundingRect() const
//{
//    return QRectF(0., 0., 10., 20.);
//}

void AbstractGraphicsWidgetResources::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF resource_rect(boundingRect());
    resource_rect.setWidth(resource_rect.width() / repeatCount());
    QPen pen;
    pen.setWidth(0); // cosmetic
    QBrush brush(Qt::SolidPattern);
    if(0){//mAssset.isNull() || mAssset->HasAffinity() == false) {
        brush.setStyle(Qt::BDiagPattern);
        brush.setTransform(painter->transform().inverted());
    }
    QColor color(color_);
    QColor light_color(color_.lighter(115));
    QColor dark_color(color_.darker(129));
    QColor light_color_border(color_.lighter(133));
    QColor dark_color_border(color_.darker(214));

    painter->save();
    for(int i = 0; i < repeatCount(); i++) {
        resource_rect.moveLeft(i * resource_rect.width());
        resource_rect = resource_rect.intersected(boundingRect());
        QRectF exposed_rect(option->exposedRect);
        if(exposed_rect.left() - 1 >= boundingRect().left())
            exposed_rect.adjust(-1, 0, 0, 0);
        if(exposed_rect.right() + 1 <= boundingRect().right())
            exposed_rect.adjust(0, 0, 1, 0);
        QRectF visible_rect(resource_rect.intersected(exposed_rect));
        if(visible_rect.isEmpty() == true)
            continue;
        visible_rect.adjust(0, 0, -1. / painter->transform().m11(), -1. / painter->transform().m22());

        if(acceptHoverEvents() == true && option->state & QStyle::State_MouseOver) {
            if(option->state & QStyle::State_Selected) {
                pen.setColor(light_color);
                brush.setColor(light_color);
            }
            else {
                pen.setColor(dark_color);
                brush.setColor(dark_color);
            }
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(visible_rect);
        }
        else {
            if(option->state & QStyle::State_Selected) {
                pen.setColor(dark_color);
                brush.setColor(dark_color);
            }
            else {
                pen.setColor(color_);
                brush.setColor(color_);
            }
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(visible_rect);
        }

        if(option->state & QStyle::State_Selected)
            pen.setColor(dark_color_border);
        else
            pen.setColor(light_color_border);
        painter->setPen(pen);
        if(exposed_rect.top() <= resource_rect.top())
            painter->drawLine(visible_rect.topLeft(), visible_rect.topRight());
        if(exposed_rect.left() <= resource_rect.left())
            painter->drawLine(visible_rect.topLeft(), visible_rect.bottomLeft());
        if(option->state & QStyle::State_Selected)
            pen.setColor(light_color_border);
        else pen.setColor(dark_color_border);
        painter->setPen(pen);
        if(exposed_rect.bottom() >= resource_rect.bottom())
            painter->drawLine(visible_rect.bottomLeft(), visible_rect.bottomRight());
        if(exposed_rect.right() >= resource_rect.right())
            painter->drawLine(visible_rect.topRight(), visible_rect.bottomRight());
    }
    painter->restore();
}

void AbstractGraphicsWidgetResources::setEntryPoint(const Duration &entry_point)
{
    double samples_per_frame = samplesPerFrame(GetCplEditRate());
    Duration new_entry_point(entry_point);
    Duration current_source_duration(sourceDuration());
    Duration current_entry_point(entryPoint());
    if(entry_point < 0)
        new_entry_point = 0;
    else if(entry_point > current_entry_point + current_source_duration - samples_per_frame)
        new_entry_point = entryPoint() + current_source_duration - samples_per_frame;
    if(current_entry_point != new_entry_point)
        emit entryPointChanged(current_entry_point, new_entry_point);
    if(current_source_duration != sourceDuration())
        emit sourceDurationChanged(current_source_duration, sourceDuration());
    updateGeometry();
    QRectF rect = boundingRect();
    rect.setWidth(intrinsicDuration().GetCount() / samples_per_frame);
    rect.moveLeft(-(entryPoint().GetCount() / samples_per_frame));
    duration_indicator_->setRect(rect);
}

void AbstractGraphicsWidgetResources::setSourceDuration(const Duration &d)
{
    double samples_per_frame = samplesPerFrame(GetCplEditRate());
    int rounded_samples_factor = (int)(samples_per_frame + 0.5);
    Duration new_source_duration(d);
    Duration current_source_duration(sourceDuration());
    if(new_source_duration < rounded_samples_factor)
        new_source_duration = rounded_samples_factor;
    else if(new_source_duration > intrinsicDuration() - entryPoint())
        new_source_duration = intrinsicDuration() - entryPoint();
    new_source_duration = (new_source_duration.GetCount() / rounded_samples_factor) * rounded_samples_factor;

    if(new_source_duration != current_source_duration)
        emit sourceDurationChanged(current_source_duration, new_source_duration);
    asset_->source_duration_ = new_source_duration.GetCount();
    updateGeometry();// notify layout resize the widget after sizeHint changed.
    QRectF rect = boundingRect();
    rect.setWidth(intrinsicDuration().GetCount() / samples_per_frame);
    rect.moveLeft(-(entryPoint().GetCount() / samples_per_frame));
    duration_indicator_->setRect(rect);
}

void AbstractGraphicsWidgetResources::resizeEvent(QGraphicsSceneResizeEvent *e)
{
    left_trim_handle_->setHeight(e->newSize().height());
    right_trim_handle_->setHeight(e->newSize().height());
    right_trim_handle_->setPos(e->newSize().width() / repeatCount(), 0);
    QRectF indicator_rect(duration_indicator_->boundingRect());
    indicator_rect.setHeight(e->newSize().height());
    duration_indicator_->setRect(indicator_rect);
}

void AbstractGraphicsWidgetResources::hideEvent(QHideEvent *e)
{
    right_trim_handle_->hide();
    left_trim_handle_->hide();
    duration_indicator_->hide();
    vertical_indicator_->hide();
}

QSizeF AbstractGraphicsWidgetResources::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    QSizeF size;
    EditRate ed = GetCplEditRate();
    qint64 duration_to_width = repeatCount() * sourceDuration().GetCount() / samplesPerFrame(ed); // need fixed.
    if(!constraint.isValid())
    {
        switch (which) {
        case Qt::MinimumSize:
        case Qt::PreferredSize:
        case Qt::MaximumSize:
            size = QSizeF(duration_to_width, -1);
            break;
        case Qt::MinimumDescent:
        case Qt::NSizeHints:
            size = QSizeF(-1, -1);
        default:
            size = QSizeF(-1, -1);
            break;
        }
    }
    else
    {
        size = constraint;
    }
    return size;
}

void AbstractGraphicsWidgetResources::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    update();
    if(left_trim_handle_->isEnabled()) left_trim_handle_->show();
    if(right_trim_handle_->isEnabled()) right_trim_handle_->show();
}

void AbstractGraphicsWidgetResources::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    update();
    left_trim_handle_->hide();
    right_trim_handle_->hide();
}

bool AbstractGraphicsWidgetResources::extendGrid(QPointF &point, eGridPosition which) const
{
    if(which == Vertical)
    {
        QPointF ret(mapFromScene(point));
        if(ret.x() > boundingRect().center().x())
            ret.setX(boundingRect().right());
        else
            ret.setX(boundingRect().left());
        return true;
    }
    return false;
}

Timecode AbstractGraphicsWidgetResources::MapToCplTimeline(const Timecode &rLocalTimecode) const {

    QPointF result = mapToScene(QPointF((qint64)((rLocalTimecode.GetOverallFrames() - entryPoint().GetCount()) / 2002), 0));
    return Timecode(GetCplEditRate(), result.x());
}

Duration AbstractGraphicsWidgetResources::MapToCplTimeline(const Duration &rLocalDuration) const {

    return Duration((qint64)(rLocalDuration.GetCount() / 2002));
}

void AbstractGraphicsWidgetResources::trimHandleInUse(eTrimHandlePos pos, bool active)
{
    if(active)
    {
        if(pos == Left || pos == Right)
        {
            old_entry_point_ = entryPoint();
            old_source_duration_ = sourceDuration();
        }
        maximizeZValue();
    }
    else
    {
        if(pos == Left)
        {
            if(old_entry_point_ != entryPoint())
            {
                GraphicsSceneComposition* ptr_scene = qobject_cast<GraphicsSceneComposition*>(scene());
                if(ptr_scene)
                {
                     ptr_scene->delegateCommand(new SetEntryPointCommand(this, old_entry_point_, entryPoint()));
                }
            }
        }
        else if(pos == Right)
        {
            GraphicsSceneComposition* ptr_scene = qobject_cast<GraphicsSceneComposition*>(scene());
            if(old_source_duration_ != sourceDuration())
            {
                ptr_scene->delegateCommand(new SetSourceDurationCommand(this, old_source_duration_, sourceDuration()));
            }
        }
        old_source_duration_ = Duration(-1);
        old_entry_point_ = Duration(-1);
        restoreZValue();
    }
    duration_indicator_->setVisible(active);
    vertical_indicator_->setVisible(active);
}

void AbstractGraphicsWidgetResources::trimResource(qint32 pos, qint32 lastPos, eTrimHandlePos trimPos)
{
    double samples_factor = samplesPerFrame(GetCplEditRate());
    int rounded_samples_factor = (int) (samples_factor + 0.5);
    QList<AbstractGraphicsWidgetResources*> resources;
    QList<AbstractGridExtension*> ignore_list;
    if(getSequence())
    {
        resources = getSequence()->resourceList();
        for(int i = 0; i < resources.count(); i++)
            ignore_list.append(resources.at(i));
    }
    if(trimPos == Left)
    {
        QRectF rect(0,0,0,0);
        rect.setWidth(qint64(old_source_duration_.GetCount() + old_entry_point_.GetCount()) / samples_factor);
        qint64 move_left = qint64(old_entry_point_.GetCount() / samples_factor);
        rect.moveLeft(-move_left);
        rect = mapRectToScene(rect);
        QPointF grid_point(rect.right() - (pos - rect.left() - move_left), 0);
        GraphicsSceneComposition* ptr_scene = qobject_cast<GraphicsSceneComposition*>(scene());
        GraphicsSceneComposition::GridInfo grid_info;
        if(ptr_scene)
        {
            QRectF search_rect;
            if(getSequence() && getSequence()->getSegment())
                search_rect = getSequence()->getSegment()->mapRectToScene(getSequence()->getSegment()->boundingRect());
            search_rect.setTop(ptr_scene->sceneRect().top());
            search_rect.setBottom(ptr_scene->sceneRect().bottom());
            grid_info = ptr_scene->SnapToGrid(grid_point, Vertical, mapRectToScene(search_rect), ignore_list);
            if(grid_info.IsVerticalSnap)
            {
                vertical_indicator_->setHeight(ptr_scene->height());
                vertical_indicator_->setPos(mapFromScene(QPointF(grid_info.SnapPos.x(), ptr_scene->sceneRect().top())));
                vertical_indicator_->show();
            }
            Duration new_entry_point = ((-grid_info.SnapPos.x() + rect.right() + rect.left()) -
                                        rect.left() + move_left) * samples_factor;
            setEntryPoint(new_entry_point);
        }
    }
    else if(trimPos == Right)
    {
        QPointF grid_point(pos, 0);
        GraphicsSceneComposition* ptr_scene = qobject_cast<GraphicsSceneComposition*>(scene());
        GraphicsSceneComposition::GridInfo grid_info;
        if(ptr_scene)
        {
            QRectF search_rect;
            if(getSequence() && getSequence()->getSegment())
                search_rect = getSequence()->getSegment()->mapRectToScene(getSequence()->getSegment()->boundingRect());
            grid_info = ptr_scene->SnapToGrid(grid_point, Vertical, search_rect, ignore_list);
            if(grid_info.IsVerticalSnap)
            {
                vertical_indicator_->setColor(grid_info.ColorAdvice);
                vertical_indicator_->setHeight(ptr_scene->height());
                vertical_indicator_->setPos(mapFromScene(QPointF(grid_info.SnapPos.x(), ptr_scene->sceneRect().top())));
                vertical_indicator_->show();
            }
            else
            {
                vertical_indicator_->hide();
            }
        }
        int local_pos = mapFromScene(QPointF(grid_info.SnapPos.x(), 0)).x();
        qDebug() << "local pos" <<local_pos;

        Duration new_source_duration = ceil(local_pos * samples_factor);
        setSourceDuration(new_source_duration);
    }
}

void AbstractGraphicsWidgetResources::maximizeZValue()
{
    setZValue(1);
    duration_indicator_->setZValue(1);
    vertical_indicator_->setZValue(1);
    GraphicsWidgetSequence* sequence = getSequence();
    if(sequence)
    {
        sequence->setZValue(1);
        GraphicsWidgetSegment* segment = sequence->getSegment();
        if(segment)
            segment->setZValue(1);
    }
}

void AbstractGraphicsWidgetResources::restoreZValue()
{
    setZValue(0);
    duration_indicator_->setZValue(0);
    vertical_indicator_->setZValue(0);
    GraphicsWidgetSequence* sequence = getSequence();
    if(sequence)
    {
        sequence->setZValue(0);
        GraphicsWidgetSegment* segment = sequence->getSegment();
        if(segment)
            segment->setZValue(0);
    }
}

GraphicsWidgetSequence* AbstractGraphicsWidgetResources::getSequence() const
{
    return qobject_cast<GraphicsWidgetSequence*>(parentObject());
}


GraphicsWidgetFileResource::GraphicsWidgetFileResource(GraphicsWidgetSequence *parent, const QColor& color)
    :AbstractGraphicsWidgetResources(parent, color)
{
}

GraphicsWidgetVideoResource::GraphicsWidgetVideoResource(GraphicsWidgetSequence *parent)
    :GraphicsWidgetFileResource(parent, QColor(COLOR_VIDEO_RESOURCE))
{

}

void GraphicsWidgetVideoResource::dropEvent(QGraphicsSceneDragDropEvent *event) {
    GraphicsWidgetFileResource::dropEvent(event);

    // 获取视频路径
    QString videoPath = event->mimeData()->text();

    // 提取视频封面和结尾图
    int err;
    QPixmap *tmp = nullptr;
    err = ThumbnailTool::extractThumbnail(videoPath, &tmp, 0);
    if(err) {
        qDebug() << "error occurs in extractThumbnail. param start = 0";
    }
    left_proxy_image_ = tmp->toImage();
    err = ThumbnailTool::extractThumbnail(videoPath, &tmp, -1);
    if(err) {
        qDebug() << "error occurs in extractThumbnail. param start = -1";
    }
    right_proxy_image_ = tmp->toImage();
    updateGeometry();
}

void GraphicsWidgetVideoResource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    AbstractGraphicsWidgetResources::paint(painter, option, widget);
    const int offset = 0; //
    QRectF resource_rect(boundingRect());
    resource_rect.setWidth(resource_rect.width() / repeatCount());
    QPen pen;
    pen.setWidth(0);
    pen.setColor(QColor(CPL_FONT_COLOR));
    painter->setPen(pen);
    painter->setFont(QFont());

    for(int i = 0; i < repeatCount(); i++)
    {
        resource_rect.moveLeft(i * resource_rect.width());
        resource_rect = resource_rect.intersected(boundingRect());
        QRectF exposed_rect(option->exposedRect);
        if(exposed_rect.left() - 1 >= boundingRect().left())
            exposed_rect.adjust(-1, 0, 0, 0);
        if(exposed_rect.right() + 1 <= boundingRect().right())
            exposed_rect.adjust(0, 0, 1, 0);
        QRectF visible_rect(resource_rect.intersected(exposed_rect));
        visible_rect.adjust(0, 0, -1. / painter->transform().m11(), -1. / painter->transform().m22());
        if(visible_rect.isEmpty() == true)
            continue;

        // scale proxy images (k)
        QImage left_proxy_image = left_proxy_image_.scaledToHeight(boundingRect().height(), Qt::SmoothTransformation);
        QImage right_proxy_image = right_proxy_image_.scaledToHeight(boundingRect().height(), Qt::SmoothTransformation);

        QTransform transf = painter->transform();

        QRectF left_proxy_image_rect(QPointF((resource_rect.left() * transf.m11() + offset) * 1 / transf.m11(), resource_rect.topLeft().y() + 1), QSizeF(left_proxy_image.width() * 1 / transf.m11(), left_proxy_image.height()));
        QRectF right_proxy_image_rect(QPointF((resource_rect.right() * transf.m11() - right_proxy_image.width() - offset - 1) * 1 / transf.m11(), resource_rect.topRight().y() + 1), QSizeF(right_proxy_image.width() * 1 / transf.m11(), right_proxy_image.height()));

        if(left_proxy_image_rect.right() <= right_proxy_image_rect.left()) {
            if(visible_rect.intersects(left_proxy_image_rect)) painter->drawImage(left_proxy_image_rect, left_proxy_image);
            if(visible_rect.intersects(right_proxy_image_rect))	painter->drawImage(right_proxy_image_rect, right_proxy_image);

//            // (k) - start
//            if (!proxysVisible) {
//                proxysVisible = true; // (so proxies don't get loaded twice...)
//                RefreshProxy();
//            }
//            // (k) - end
        }
        else {
//            left_proxy_image_rect.setWidth(0);
//            right_proxy_image_rect.setLeft(right_proxy_image_rect.right());
            if(visible_rect.intersects(left_proxy_image_rect)) painter->drawImage(left_proxy_image_rect, left_proxy_image);
        }

        QFontMetricsF font_metrics(painter->font());
        QRectF writable_rect(left_proxy_image_rect.topRight(), right_proxy_image_rect.bottomLeft());
        writable_rect.adjust(5 / transf.m11(), 0, -5 / transf.m11(), -2);

        if(writable_rect.isEmpty() == false) {

            QString duration("Duration");//font_metrics.elidedText(tr("Dur.: %1").arg(MapToCplTimeline(sourceDuration()).GetCount()), Qt::ElideLeft, writable_rect.width() * transf.m11()));
            QString file_name;
            if((mAssset) && mAssset->HasAffinity()) {
                if(i == 0)
                    file_name = "File"; //QString(font_metrics.elidedText(mAssset->GetOriginalFileName().first, Qt::ElideRight, writable_rect.width() * transf.m11() - font_metrics.width(duration)));
                else file_name = QString(font_metrics.elidedText(tr("[Duplicate]"), Qt::ElideRight, writable_rect.width() * transf.m11() - font_metrics.horizontalAdvance(duration)));
            } else if ((mAssset) && (!mAssset->HasAffinity()) && (mAssset->GetIsOutsidePackage())) {
                pen.setColor(mAssset->GetColor());
                painter->setPen(pen);
                if(i == 0)
                    file_name = QString(font_metrics.elidedText("OV Asset: " + mAssset->GetOriginalFileName(), Qt::ElideRight, writable_rect.width() * transf.m11() - font_metrics.horizontalAdvance(duration)));
                else
                    file_name = QString(font_metrics.elidedText(tr("[Duplicate]"), Qt::ElideRight, writable_rect.width() * transf.m11() - font_metrics.horizontalAdvance(duration)));
            }
            QString cpl_out_point(font_metrics.elidedText(tr("Cpl Out: %1").arg(MapToCplTimeline(Timecode(editRate(), entryPoint() + (i + 1) * sourceDuration() - 1)).GetAsString()), Qt::ElideLeft, writable_rect.width() * transf.m11()));
            QString cpl_in_point(font_metrics.elidedText(tr("Cpl In: %1").arg(MapToCplTimeline(Timecode(editRate(), entryPoint() + (i * (sourceDuration())))).GetAsString()), Qt::ElideRight, writable_rect.width() * transf.m11() - font_metrics.horizontalAdvance(cpl_out_point)));

            QString resource_out_point(font_metrics.elidedText(tr("Out: %1").arg(Timecode(editRate(), entryPoint() + sourceDuration() - 1).GetAsString()), Qt::ElideLeft, writable_rect.width() * transf.m11()));
            QString resource_in_point(font_metrics.elidedText(tr("In: %1").arg(Timecode(editRate(), entryPoint()).GetAsString()), Qt::ElideRight, writable_rect.width() * transf.m11() - font_metrics.horizontalAdvance(cpl_out_point)));

            painter->setTransform(QTransform(transf).scale(1 / transf.m11(), 1).translate(writable_rect.left() * transf.m11(), writable_rect.top() + font_metrics.height())); // We have to use QTransform::translate() because of bug 192573.
            painter->drawText(QPointF(0, 0), file_name);
            painter->setTransform(QTransform(transf).scale(1 / transf.m11(), 1).translate((writable_rect.right() * transf.m11() - font_metrics.horizontalAdvance(duration)), writable_rect.top() + font_metrics.height()));
            painter->drawText(QPointF(0, 0), duration);

            painter->setTransform(QTransform(transf).scale(1 / transf.m11(), 1).translate(writable_rect.left() * transf.m11(), writable_rect.bottom()));
            painter->drawText(QPointF(0, 0), cpl_in_point);
            painter->setTransform(QTransform(transf).scale(1 / transf.m11(), 1).translate((writable_rect.right() * transf.m11() - font_metrics.horizontalAdvance(cpl_out_point)), writable_rect.bottom()));
            painter->drawText(QPointF(0, 0), cpl_out_point);

            painter->setTransform(QTransform(transf).scale(1 / transf.m11(), 1).translate(writable_rect.left() * transf.m11(), writable_rect.top()));
            painter->drawText(QPointF(0, 35), resource_in_point);
            painter->setTransform(QTransform(transf).scale(1 / transf.m11(), 1).translate((writable_rect.right() * transf.m11() - font_metrics.horizontalAdvance(resource_out_point)), writable_rect.top()));
            painter->drawText(QPointF(0, 35), resource_out_point);

            painter->setTransform(transf);
        }
    }
}

void GraphicsWidgetVideoResource::trimHandleInUse(eTrimHandlePos pos, bool active)
{
    GraphicsWidgetFileResource::trimHandleInUse(pos, active);
    is_trim_active_ = active;
    if(!is_trim_active_)
    {
        switch (pos) {
        case Left:
            slot_entry_point_changed();
            break;
        case Right:
            slot_source_duration_changed();
            break;
        default:
            break;
        }
    }
}



void GraphicsWidgetVideoResource::slot_entry_point_changed()
{
    if(!is_trim_active_)
    {
        // RefreshProxy();
    }
}

void GraphicsWidgetVideoResource::slot_source_duration_changed()
{
    if(!is_trim_active_)
    {
        // RefreshProxy();
    }
}

GraphicsWidgetAudioResource::GraphicsWidgetAudioResource(GraphicsWidgetSequence *parent)
    :GraphicsWidgetFileResource(parent, QColor(COLOR_AUDIO_RESOURCE))
{

}

GraphicsWidgetTimedTextResource::GraphicsWidgetTimedTextResource(GraphicsWidgetSequence *parent)
    :GraphicsWidgetFileResource(parent, QColor(CPL_COLOR_TIMED_TEXT_RESOURCE))
{

}
