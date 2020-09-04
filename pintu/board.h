#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QMimeData>
#include <QGraphicsScene>
#include "manager.h"

//空的小块，用来接收拼图
class BoardPiece : public QGraphicsObject {
public:
    BoardPiece(const char * imagePath, int x, int y, int w, int h, int id, PieceManager *manager);
    QRectF boundingRect() const override {
        return QRectF(this->pos().x(), this->pos().y(), this->width, this->height);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        this->image = this->image.scaled(this->width, this->height);
        painter->drawImage(this->pos().x(), this->pos().y(), this->image);
    }
    friend class Piece;

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

protected:
    QImage image;
    int width;
    int height;
    int id;
    int id2 = 0;
    bool dragEnd;
    bool filled;
    PieceManager *manager;
};

#endif // BOARD_H
