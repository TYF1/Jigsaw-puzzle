#ifndef QPAINT_H
#define QPAINT_H
#include <QPainter>
#include <QWidget>

class PaintedWidget : public QWidget
{
    Q_OBJECT
public:
    PaintedWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QPAINT_H
