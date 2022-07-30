#include <cmath>
#include <QPainter>
#include "ball.h"
#include "constants.h"

Ball::Ball(qreal x, qreal y)
{
    setPos(x, y);       // 设置小球位置

    // 初始化所有方向所有维度的加速度为0
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < forceCount; j++)
            a[i][j] = 0;
}

// 小球的形状
QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(QPointF(0, 0), BALL_SIZE / 2, BALL_SIZE / 2); // 此坐标为本地坐标系
    return path;
}

QRectF Ball::boundingRect() const
{
    return QRectF(-BALL_SIZE * 2, -BALL_SIZE * 2, BALL_SIZE * 4, BALL_SIZE * 4);    // 此坐标为本地坐标系
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);     // 设置反走线（抗锯齿）
    painter->fillPath(shape(), Qt::blue);

    painter->restore();
}

void Ball::advance(int phase)
{
    // 只有phase为1时进行处理
    if (!phase) return ;

    // 计算合力
    qreal sumAx = 0, sumAy = 0;
    for (int i = 0; i < forceCount; i++)
    {
        sumAx += a[xAxis][i];
        sumAy += a[yAxis][i];
    }

    if (sumAx) vx += (sumAx / FRAME_RATE);
    if (sumAy) vy += (sumAy / FRAME_RATE);

    qreal x = fmod(pos().rx() + vx / FRAME_RATE, 1000), y = fmod(pos().ry() + vy / FRAME_RATE, 1000);

    // 处理小球越界
    if (x < 0) x += 1000;
    if (y < BALL_SIZE / 2) y = BALL_SIZE / 2;

    // 设置新位置
    setPos(QPointF(x, y));
    update();       // 更新显示小球
}
