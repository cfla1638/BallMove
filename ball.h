#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>

class Ball : public QGraphicsItem
{
public:
    Ball(qreal x, qreal y);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void advance(int phase);
    QPointF getPos(){return pos();}

    int forceCount = 4;
    qreal a[2][4];
    qreal vx = 0;
    qreal vy = 0;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

#endif // BALL_H
