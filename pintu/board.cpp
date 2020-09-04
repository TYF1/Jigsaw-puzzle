#include "board.h"
#include "conf.h"
#include <QMessageBox>
#include <QPushButton>

BoardPiece::BoardPiece(const char * imagePath, int x, int y,int w, int h, int id, PieceManager *manager) {
    this->setAcceptDrops(true);
    this->setPos(x, y);
    this->width = w;
    this->height = h;
    this->id = id;
    QImage img;
    img.load(imagePath);
    this->image = img;
    this->manager = manager;
}

//拖入触发事件
void BoardPiece::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
   event->setAccepted(true);
}

//拖出触发事件
void BoardPiece::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
   event->setAccepted(false);
}

//放下触发事件
void BoardPiece::dropEvent(QGraphicsSceneDragDropEvent *event) {
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

    //将所拖拽的拼图块的位置设为拖入空白块的位置
    if(mime->hasImage()) {
        this->id2 = mime->data(QMetaType::typeName(QMetaType::Int)).toInt();
        this->manager->getPieceById(this->id2)->id2 = this->id;
        this->manager->getPieceById(this->id2)->setRotation(0);
        this->manager->getPieceById(this->id2)->setPos(this->pos());
        if(this->id == this->id2) {
            this->manager->setPieceCompleteById(this->id2, true);
        }
        else {
            this->manager->setPieceCompleteById(this->id2, false);
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

    update();
}
