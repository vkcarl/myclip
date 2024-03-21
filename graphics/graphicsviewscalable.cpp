#include "graphicsviewscalable.h"
#include <QGraphicsItem>
GraphicsViewScalable::GraphicsViewScalable(QWidget* parent)
    :QGraphicsView(parent)
{
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Work around(skip the problem): Disable funny behavior of exposedrect.
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    //setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void GraphicsViewScalable::zoomIn()
{
    scaleView(1 / qreal(1.1));
}

void GraphicsViewScalable::zoomOut()
{
    scaleView(qreal(1.1));
}

eScaleStatus GraphicsViewScalable::scaleView(qreal scaleFactor) {
    QTransform t = transform().scale(scaleFactor, 1.0);
    qreal factor = t.mapRect(QRectF(0, 0, 1, 1)).width();
    if(factor < 0.007)
        return ScaleMin;
    else if(factor > 50)
        return ScaleMax;
    QTransform matrix;
    QRectF viewPortRect = this->viewport()->rect();
    QRectF sceneRect = this->sceneRect();
    if(sceneRect.width() * t.m11() - viewPortRect.width() < 0)
   {
        qreal tt = viewPortRect.width() / sceneRect.width();
        matrix = QTransform(tt, t.m12(), t.m21(), t.m22(), t.dx(), t.dy());
        this->setTransform(matrix, false);
        status_ = ScaleMin;
    }
    else
    {
        this->setTransform(t);
        status_ = ScaleNormal;
    }

    QList<QGraphicsItem*> items_list(items());
    for(int i = 0; i < items_list.size(); i++) {
        AbstractViewTransformNotifier* pItem = dynamic_cast<AbstractViewTransformNotifier*>(items_list.at(i));
        if(pItem) {
            pItem->ViewTransformEvent(transform());
        }
    }
    return status_;
}
