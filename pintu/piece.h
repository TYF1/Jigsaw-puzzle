#ifndef PIECE_H
#define PIECE_H

#include <random>
#include <time.h>
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QApplication>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QMetaType>
#include "windows.h"
#include "manager.h"

class PieceManager;

//拼图碎片
class Piece : public QGraphicsObject {
public:
    Piece(const char * imagePath, int w, int h, int id, PieceManager *manager);
    QRectF boundingRect() const override {
        return QRectF(this->pos().x(), this->pos().y(), this->width, this->height);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        this->image = this->image.scaled(this->width, this->height);
        painter->drawImage(this->pos().x(), this->pos().y(), this->image);
    }
    void toOrigin() {
        this->setPos(this->initX, this->initY);
        this->setRotation(this->initR);
    }
    friend class BoardPiece;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

protected:
    QImage image;
    int width;
    int height;
    int id;
    int id2 = 0;
    int initX;
    int initY;
    int initR;
    PieceManager *manager;
};

#endif // PIECE_H
