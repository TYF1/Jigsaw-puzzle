#include "piece.h"
#include "conf.h"
#include <QDrag>
#include <QMimeData>
#include <QMessageBox>
#include <QPushButton>
#include "mainwindow.h"

Piece::Piece(const char *imagePath, int w, int h, int id, PieceManager *manager)  {
    this->setAcceptDrops(true);
    this->width = w;
    this->height = h;
    this->id = id;
    QImage img;
    img.load(imagePath);
    this->image = img;
    int initX = rand() % (2 * BasicPieceSize) + 5000 / w;
    int initY = rand() % (2 * BasicPieceSize) + 5000 / h;
    int initR = rand() % 60 - 30;
    this->initX = initX;
    this->initY = initY;
    this->initR = initR;
    this->setPos(initX, initY);
    this->setRotation(initR);
    this->manager = manager;
}

//按下鼠标触发事件
void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    setCursor(Qt::ClosedHandCursor);
}

//鼠标移动触发事件
void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    this->manager->win->drag = new QDrag((QObject*)event->widget());
    QMimeData *mime = new QMimeData;

    mime->setImageData(this->image);
    mime->setData(QString(QMetaType::typeName(QMetaType::Int)), QString("%1").arg(this->id).toLatin1());

    this->manager->win->drag->setMimeData(mime);

    this->manager->win->drag->setPixmap(QPixmap::fromImage(this->image));

    this->manager->win->drag->setHotSpot(QPoint(this->width / 2, this->height / 2));

    this->manager->win->released = false;
    this->manager->win->drag->exec();
    this->manager->win->released = true;

    setCursor(Qt::OpenHandCursor);
}

//松开鼠标触发事件
void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    setCursor(Qt::OpenHandCursor);
}

//拖入触发事件
void Piece::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    event->setAccepted(true);
}

//拖出触发事件
void Piece::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    event->setAccepted(false);
}

//放下触发事件
void Piece::dropEvent(QGraphicsSceneDragDropEvent *event) {
    auto mwin = this->manager->win;
    if(mwin->a == 0) {
        mwin->timer1->stop();
        int to;
        to = QMessageBox::warning(NULL,"timeout","timeout",QMessageBox::Ok);
        if(to == QMessageBox::Ok){
            mwin->backBtn2->click();
            mwin->shizhong->m_textColor =Qt::black;
            mwin->shizhong->m_boderColor =QColor(54, 54, 54);;
            mwin->shizhong->m_bgColor =Qt::white;
            mwin->shizhong->m_usedColor=QColor(0,245,255);
        }
        return;
    }
    const QMimeData *mime = event->mimeData();
    if(mime->hasImage()) {
        int id2 = mime->data(QMetaType::typeName(QMetaType::Int)).toInt();
        auto ptr = this->manager->getPieceById(id2);
        int tempX = ptr->initX, tempY = ptr->initY, tempR = ptr->rotation();
        ptr->initX = this->initX;
        ptr->initY = this->initY;
        ptr->setRotation(this->rotation());
        this->initX = tempX;
        this->initY = tempY;
        this->setRotation(tempR);
        auto tempPos = ptr->pos();
        ptr->setPos(this->pos());
        this->setPos(tempPos);
        int tempId2 = ptr->id2;
        ptr->id2 = this->id2;
        this->id2 = tempId2;
        if(this->id == this->id2) {
            this->manager->setPieceCompleteById(this->id, true);
        }
        else {
            this->manager->setPieceCompleteById(this->id, false);
        }
        if(ptr->id == ptr->id2) {
            ptr->manager->setPieceCompleteById(ptr->id, true);
        } else {
            ptr->manager->setPieceCompleteById(ptr->id, false);
        }
        this->manager->tempScoreAdd = 0;
        for(auto iter = this->manager->checkMap.begin(); iter != this->manager->checkMap.end(); iter++) {
            if(iter->second)
                this->manager->tempScoreAdd += mwin->level / 2;
        }
        if(this->manager->isComplete()) {

            this->manager->tempScoreAdd = 0;

            int stb = mwin->level * mwin->level * 100 + mwin->a * mwin->level;

            if(mwin->levelScore.find(mwin->level) != mwin->levelScore.end()) {
                if(stb > mwin->levelScore.find(mwin->level)->second) {
                    mwin->levelScore[mwin->level] = stb;
                }
            } else {
                mwin->levelScore[mwin->level] = stb;
            }

            mwin->addUpScore();

            mwin->timer1->stop();
            mwin->fen1->setValue(mwin->score);

            auto val = QMessageBox::question(mwin, "Zhao Cong Puzzle", "Congratulations! Next?", QMessageBox::Yes | QMessageBox::No);

            if (val == QMessageBox::Yes) {

                mwin->level++;
                if(mwin->level < 4)
                    mwin->gamej();
                else if(mwin->level >= 4 && mwin->level < 7)
                    mwin->gamez();
                else if(mwin->level >= 7 && mwin->level < 10)
                    mwin->gamek();
                else if(mwin->level >= 10 && mwin->level < 13)
                    mwin->gamee();
                else if(mwin->level >= 13)
                    mwin->gamed();
            } else if (val == QMessageBox::No) {
                mwin->backBtn2->click();
            }
        }
    }
}
