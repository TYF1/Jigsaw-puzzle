#include "mainwindow.h"
#include <QApplication>
#include <qpaint.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include<QPaintEngine>
#include<QPainter>
#include<QPaintDevice>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow win;
    win.show();

    return app.exec();
}
