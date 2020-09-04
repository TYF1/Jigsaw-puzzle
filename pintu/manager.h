#ifndef MANAGER_H
#define MANAGER_H

#include "mainwindow.h"
#include "piece.h"
#include <QGraphicsScene>
#include <map>

using namespace std;

class Piece;

class MainWindow;

//用来在碎片和空白块之间传递数据
class PieceManager {
public:
    PieceManager() {}
    PieceManager(QGraphicsScene *scene, MainWindow *win) {
        this->scene = scene;
        this->win = win;
    }
    //添加一块拼图
    void addPiece(int id, Piece *piece);
    //根据id返回对应的拼图碎片
    Piece* getPieceById(int id) {
        if(this->srcPiecesMap.find(id) != this->srcPiecesMap.end()) {
            return this->srcPiecesMap.find(id)->second;
        }
        return nullptr;
    }
    //将对应id的拼图碎片设为完成状态
    void setPieceCompleteById(int id, bool status) {
        this->checkMap[id] = status;
    }
    //检查对应id的拼图碎片是否是完成状态
    bool getPieceCompleteById(int id) {
        if(this->checkMap.find(id) != this->checkMap.end()) {
            return this->checkMap.find(id)->second;
        }
        return false;
    }
    //移除所有拼图碎片
    void removeAllPieces() {
        for(int i = 1; ; i++) {
            if(srcPiecesMap.find(i) != srcPiecesMap.end()) {
                scene->removeItem(reinterpret_cast<QGraphicsObject*>(srcPiecesMap.find(i)->second));
            } else {
                break;
            }
        }
    }
    //重置
    void flushManager() {
        this->removeAllPieces();
        srcPiecesMap.clear();
        checkMap.clear();
        tempScoreAdd = 0;
    }
    //是否全部拼图碎片都是完成状态
    bool isComplete();

    friend class Piece;
    friend class BoardPiece;
    friend class Blank;
    friend class MainWindow;
    friend void addOne(const string type, const string piecePathRoot, const string rootName, int rows, int id, PieceManager *manager);
    friend void SubGame(const string rootName, const string originName, const int size, PieceManager *manager);

private:
    MainWindow *win;                    //程序的主窗口
    QGraphicsScene *scene;              //画布
    map< int, Piece* > srcPiecesMap;    //碎片id 和 碎片 的map
    map< int, bool > checkMap;          //碎片id 和 完成状态 的map
    int tempScoreAdd = 0;
};

#endif // MANAGER_H
