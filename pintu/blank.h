#ifndef BLANK_H
#define BLANK_H

#include "conf.h"
#include <QGraphicsObject>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QMimeData>
#include <QGraphicsScene>
#include "manager.h"
#include "conf.h"

//放碎片的桌子
class Blank : public QGraphicsObject {
public:
    Blank(PieceManager *manager) {
        QImage img;
        img.load("./images/bg.jpg");
        this->image = img;
        this->manager = manager;
        this->setAcceptDrops(true);
    }
    QRectF boundingRect() const override {
        return QRectF(0, 0, BlankWidth, BlankHeight);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        this->image = this->image.scaled(ViewWidth, ViewHeight);
        painter->drawImage(0, 0, this->image);
        Q_UNUSED(option);
        Q_UNUSED(widget);
    }
protected:
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
private:
    PieceManager *manager;
    QImage image;
};

#endif // BLANK_H
