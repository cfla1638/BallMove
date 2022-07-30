#include <QFont>
#include <QPainter>
#include <QString>

#include "ball.h"
#include "balldata.h"
#include "constants.h"


ballData::ballData(Ball * ball) : ball(ball)
{
    setPos(0, 0);
}

QPainterPath ballData::shape() const
{
    QPainterPath path;

    QFont font;
    font.setPixelSize(40);
    path.addText(QPointF(0, 40), font, QString("x:") + QString::number(ball->getPos().x()));
    path.addText(QPointF(0, 80), font, QString("y:") + QString::number(ball->getPos().y()));

    path.addText(QPointF(300, 40), font, QString("Vx:") + QString::number(ball->vx));
    path.addText(QPointF(300, 80), font, QString("Vy:") + QString::number(ball->vy));

    path.addText(QPointF(0, 160), font, QString("User Ax:") + QString::number(ball->a[xAxis][User]));
    path.addText(QPointF(0, 200), font, QString("User Ay:") + QString::number(ball->a[yAxis][User]));

    path.addText(QPointF(300, 160), font, QString("Friction Ax:") + QString::number(ball->a[xAxis][Friction]));
    path.addText(QPointF(300, 200), font, QString("Friction Ay:") + QString::number(ball->a[yAxis][Friction]));

    path.addText(QPointF(700, 160), font, QString("Air Ax:") + QString::number(ball->a[xAxis][AirResistance]));
    path.addText(QPointF(700, 200), font, QString("Air Ay:") + QString::number(ball->a[yAxis][AirResistance]));

    return path;
}

QRectF ballData::boundingRect() const
{
    return QRectF(-50, -50, 1050, 450);
}

void ballData::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->fillPath(shape(), Qt::green);
    painter->restore();
}
