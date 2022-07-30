#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

class ballData;
class QGraphicsScene;
class Ball;
class QTimer;
class QKeyEvent;
class Ground;

class Controller : QObject
{
    Q_OBJECT

public:
    Controller(QGraphicsScene & scene, QObject * parent = 0);
    void track(bool);
    void gravity();

public slots:
    void drawLineOfTrack();
    void resume();
    void pause();
    void advance();

protected:
    bool eventFilter(QObject *atched, QEvent *event);

private:
    void handleKeyPressed(QKeyEvent * event);
    void handleKeyReleased(QKeyEvent * event);

    QTimer timer;
    Ball * ball;
    QGraphicsScene & scene;
    Ground * ground;
    ballData * data;

};

#endif // CONTROLLER_H
