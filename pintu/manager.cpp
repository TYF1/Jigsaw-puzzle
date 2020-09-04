#include "manager.h"

//添加一块
void PieceManager::addPiece(int id, Piece *piece) {
    this->scene->addItem(piece);
    this->srcPiecesMap[id] = piece;
    this->checkMap[id] = false;
}

//检查拼图是否完成
bool PieceManager::isComplete() {
    for(auto i = this->checkMap.begin(); i != this->checkMap.end(); i++) {
        if(i->second == false)
            return false;
    }
    return true;
}
