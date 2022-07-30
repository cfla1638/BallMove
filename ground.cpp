#include <QPainter>
#include "ground.h"

Ground::Ground(qreal x, qreal y)
{
    setPos(x, y);
}

QRectF Ground::boundingRect() const
{
    return QRectF(-1200, -100, 2400, 400);
}

QPainterPath Ground::shape() const
{
    QPainterPath path;
    path.addRect(-1000, 0, 2000, 200);
    return path;
}

void Ground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    painter->fillPath(shape(), Qt::black);

    painter->restore();
}
