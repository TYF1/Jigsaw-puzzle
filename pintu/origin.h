#ifndef ORIGIN_H
#define ORIGIN_H

#include <QPainter>
#include <QGraphicsObject>
#include "conf.h"
#include <string>

using namespace std;

//原图
class Origin : public QGraphicsObject {
public:
    Origin(const char* picName) {
        this->picName = picName;
        QImage img;
        img.load(picName);
        this->image = img;
        this->setPos(606, 320);
    }
    QRectF boundingRect() const override {
        return QRectF(this->pos().x(), this->pos().y(), 180, 180);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        this->image = this->image.scaled(180, 180);
        painter->drawImage(this->pos().x(), this->pos().y(), this->image);
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        this->setScale(2);
        this->setPos(303, 160);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        this->setScale(1);
        this->setPos(606, 320);
    }
private:
    QImage image;
    const char *picName;
};

#endif // ORIGIN_H
