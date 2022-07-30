#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsView;
class QGraphicsScene;
class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void adjustViewSize();

private:
    void initScene();
    QGraphicsView * view;
    QGraphicsScene * scene;
    Controller * controller;
};
#endif // MAINWINDOW_H
