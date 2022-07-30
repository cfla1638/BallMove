#ifndef GROUND_H
#define GROUND_H

#include <QGraphicsItem>

class Ground : public QGraphicsItem
{
public:
    Ground(qreal x, qreal y);
    QRectF boundingRect() const;
    QPainterPath shape() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // GROUND_H
