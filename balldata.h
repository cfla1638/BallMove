#ifndef BALLDATA_H
#define BALLDATA_H

#include <QGraphicsItem>

class Ball;

class ballData : public QGraphicsItem
{
public:
    ballData(Ball * ball);

    QPainterPath shape() const;
    QRectF boundingRect() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    Ball * ball;
};

#endif // BALLDATA_H
