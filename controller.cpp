#include <cmath>
#include <QGraphicsScene>
#include <QEvent>
#include <QKeyEvent>
#include <QPainter>
#include "ball.h"
#include "ground.h"
#include "balldata.h"
#include "constants.h"
#include "controller.h"


Controller::Controller(QGraphicsScene & scene, QObject * parent)
    : QObject(parent),
      ball(new Ball(500, 500)),
      scene(scene),
      ground(new Ground(500, 800)),
      data(new ballData(ball))
{
    timer.start(1000 / FRAME_RATE);         // 计时器开始计时
    scene.installEventFilter(this);         // 安装事件过滤器
    scene.addItem(ball);                    // 添加小球
    scene.addItem(ground);                  // 添加地面
    scene.addItem(data);                    // 添加小球信息显示
    resume();                               // 开始运动
    track(false);                           // 默认关闭显示轨迹
}

void Controller::advance()
{
    scene.advance();                        // 首先调用场景的advance()

    // 获取碰撞信息
    static bool lastStatus = false;         // 上一帧是否碰撞
    static bool nowStatus = false;          // 当前是否处于碰撞
    nowStatus = ball->collidesWithItem(ground);

    //处理碰撞
    if (nowStatus == true && lastStatus == false)
    {
        ball->a[yAxis][Gravity] = 0;        // 碰撞时重力与支持力抵消
        ball->vy = -(ball->vy * 0.667);     // 回弹 2/3 的速度
        ball->a[yAxis][User] = 0;           // 竖直方向速度为0
    }

    // 处理摩擦力
    if (nowStatus)
    {
        if (ball->vx > FRICTION_SENSITIVITY) ball->a[xAxis][Friction] = -FRICTION;
        else if (ball->vx < -FRICTION_SENSITIVITY) ball->a[xAxis][Friction] = FRICTION;
        else ball->a[xAxis][Friction] = 0;
    }

    // 没有碰撞的时候
    if (!nowStatus)
    {
        // 摩擦力置零
        ball->a[xAxis][Friction] = 0;
        ball->a[yAxis][Gravity] = GRAVITY;
    }

    // 处理空气阻力
    qreal sumV = pow(ball->vx, 2) + pow(ball->vy, 2);
    if (fabs(sumV) > 10)
    {
        qreal airSum = 0.0009744 * sumV / 250;
        if (sumV == 0) sumV = 1;
        ball->a[xAxis][AirResistance] = (fabs(ball->vx) / (sqrt(sumV))) * airSum;
        ball->a[yAxis][AirResistance] = (fabs(ball->vy) / (sqrt(sumV))) * airSum;

        if (ball->vx > 5) ball->a[xAxis][AirResistance] *= -1;
        else if (ball -> vx < 10) ;
        else ball->a[xAxis][AirResistance] = 0;

        if (ball->vy > 5) ball->a[yAxis][AirResistance] *= -1;
        else if (ball -> vy < 10) ;
        else ball->a[yAxis][AirResistance] = 0;
    }


    lastStatus = nowStatus;
    data->update();                         // 更新数据显示
}

// 显示轨迹的辅助函数
void Controller::drawLineOfTrack()
{
    static QPointF last(500, 500);
    QPointF now = ball->getPos();

    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidthF(7.5);
    pen.setCapStyle(Qt::RoundCap);

    if (fabs(last.x() - now.x()) < 50 && fabs(last.y() - now.y()) < 50)
        scene.addLine(last.x(), last.y(), now.x(), now.y(), pen);
    last = now;
}


// 显示轨迹
void Controller::track(bool flag)
{
    if (flag)
        connect(&timer, SIGNAL(timeout()), this, SLOT(drawLineOfTrack()));
    else
        disconnect(&timer, SIGNAL(timeout()), this, SLOT(drawLineOfTrack()));
}

void Controller::resume()
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(advance()));
}

void Controller::pause()
{
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(advance()));
}

bool Controller::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    else if (event->type() == QEvent::KeyRelease)
    {
        handleKeyReleased((QKeyEvent *)event);
        return true;
    }
    else
    {
        return QObject::eventFilter(watched, event);
    }
}

void Controller::handleKeyPressed(QKeyEvent *event)
{
    static bool trackStatus = false;

    switch (event->key()) {
        case Qt::Key_Left:
            ball->a[xAxis][User] -= X_SPEED;
            break;
        case Qt::Key_Right:
            ball->a[xAxis][User] += X_SPEED;
            break;
        case Qt::Key_Up:
            ball->a[yAxis][User] -= Y_SPEED;
            break;
        case Qt::Key_Down:
            ball->a[yAxis][User] += Y_SPEED;
            break;
        case Qt::Key_P:
            ball->a[xAxis][User] = 0;
            ball->a[xAxis][User] = 0;
            ball->vx = 0;
            ball->vy = 0;
            break;
        case Qt::Key_C:
            scene.clear();
            ball = new Ball(500, 500);
            scene.addItem(ball);
            ground = new Ground(500, 800);
            scene.addItem(ground);
            data = new ballData(ball);
            scene.addItem(data);
            break;
        case Qt::Key_T:
            trackStatus = !trackStatus;
            track(trackStatus);
            break;
    }
}

void Controller::handleKeyReleased(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            ball->a[xAxis][User] = 0;
            break;
        case Qt::Key_Right:
            ball->a[xAxis][User] = 0;
            break;
        case Qt::Key_Up:
            ball->a[yAxis][User] = 0;
            break;
        case Qt::Key_Down:
            ball->a[yAxis][User] = 0;
            break;
    }
}
