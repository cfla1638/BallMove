#include <QGraphicsScene>
#include <QGraphicsView>
#include "mainwindow.h"
#include "controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    controller = new Controller(*scene, this);
    setCentralWidget(view);
    resize(750, 750);

    initScene();
    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::initScene()
{
    scene->setSceneRect(0, 0, 1000, 1000);
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}
