#include "blank.h"
#include "conf.h"
#include <QPushButton>

//放下触发事件
void Blank::dropEvent(QGraphicsSceneDragDropEvent *event) {
    if(this->manager->win->a == 0) {
        this->manager->win->timer1->stop();
        int to;
        to = QMessageBox::warning(NULL,"timeout","timeout",QMessageBox::Ok);
        if(to == QMessageBox::Ok){
            this->manager->win->backBtn2->click();
            this->manager->win->shizhong->m_textColor =Qt::black;
            this->manager->win->shizhong->m_boderColor =QColor(54, 54, 54);;
            this->manager->win->shizhong->m_bgColor =Qt::white;
            this->manager->win->shizhong->m_usedColor=QColor(0,245,255);
        }
        return;
    }

    const QMimeData *mime = event->mimeData();

    //将拖入的拼图块放回最初的位置
    if(mime->hasImage()) {
        int id2 = mime->data(QMetaType::typeName(QMetaType::Int)).toInt();
        this->manager->checkMap[id2] = false;
        this->manager->getPieceById(id2)->toOrigin();
    }

    update();
}
