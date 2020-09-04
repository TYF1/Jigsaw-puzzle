#include "mainwindow.h"
#include <QApplication>
#include "manager.h"
#include "piece.h"
#include "board.h"
#include "blank.h"
#include "origin.h"
#include "conf.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void addOne(const string type, const string piecePathRoot, const string rootName,int rows, int id, PieceManager *manager) {
    float sizeRatio = 5.0 / (float)rows;
    int pSize = BasicPieceSize * sizeRatio;
    int row = (id - 1) / rows + 1;
    int col = (id % rows == 0 ? rows : id % rows);
    if(type == "board") {
        BoardPiece *board = new BoardPiece("./images/board.png", BoardCenterX + (col - 1) * pSize / 2, BoardCenterY + (row -1) * pSize / 2, pSize, pSize, id, manager);
        manager->scene->addItem(board);
    }
    else {
        string imgName = rootName + "_" + (id < 10 ? ("0" + to_string(id)) : to_string(id)) + ".png";
        Piece *piece = new Piece((piecePathRoot + imgName).c_str(), pSize, pSize, id, manager);
        manager->addPiece(id, piece);
    }
}

void SubGame(const string rootName, const string originName, const int size, PieceManager *manager) {
    manager->removeAllPieces();
    for(int i = 1; i <= size * size; i++) {
        addOne("board" ,("./images/" + rootName + "/").c_str(), rootName, size, i, manager);
    }
    for(int i = 1; i <= size * size; i++) {
        addOne("piece" ,("./images/" + rootName + "/").c_str(), rootName, size, i, manager);
    }

    Origin *origin = new Origin(("./images/" + rootName + "/" + originName).c_str());
    manager->scene->addItem(origin);
}
