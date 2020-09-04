#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QSlider>
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDrag>
#include <QPainter>
#include <QTimer>
#include <QString>
#include <QMediaPlayer>
#include <QList>
#include<QMediaPlaylist>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTableView>
#include <QHeaderView>
#include <QTableView>
#include <QStandardItemModel>
#include <QListWidget>
#include "manager.h"
#include "jishi.h"
#include <QSet>
#include "fen.h"
#include <map>

using namespace std;

class PieceManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    friend class Piece;
    friend class BoardPiece;
    friend class Blank;

    int level = 1;
    map<int, int> levelScore;
    int score = 0;
    int a;          //剩余时间

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void inst();
    void quit();
    void start();
    void addUpScore();
    void gamej();
    void gamez();
    void gamek();
    void gamee();
    void gamed();
    void changeM();



    void writeUsername(QString playerName);
    void rankList();
    void interUsername();
    void writeScore(QString playerName);
    void namelist(QString playerName);

    QSet<QString> name1;

    QList<QString> name;
    QList<int> scores1;



    void update1();
    void keyPressEvent(QKeyEvent *e);
    void xiao();
    QTimer *timer1;
    QLabel  *printer;
private:
    Ui::MainWindow *ui;
    int value;
    int n;
    QDialog dialog1;
    QDialog dialog2;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btn10;
    QPushButton *btn11;
    QPushButton *btn12;
    void playerlist();
    void volumedialog();
    QWidget wid1;
    QSlider *slider;
    QListWidget *listWidget;
    QMediaPlayer *Mplayer;
    QMediaPlayer *Mplayers;
    QMediaPlaylist *Mplaylist;
    QTableView  *views;
    QStandardItemModel  *model;
    QAction *playAction;
    QAction *quitAction;
    QAction *instAction;
    QAction *rankAction;
    QAction *voluAction;
    QAction *CbgmAction;
    QPushButton *startBtn;
    QPushButton *rankBtn;
    QPushButton *quitBtn;
    QPushButton *jiandan;
    QPushButton *zhongdeng;
    QPushButton *kunnan;
    QPushButton *emeng;
    QPushButton *diyu;
    QPushButton *backBtn;
    QPushButton *backBtn2;
    QGraphicsScene _scene;
    QGraphicsView _view;
    QPixmap _pix;
    bool _pressed;
private slots:
        void clear();
        void changevolume(int n);
        void musicplay();
        void playbackmode();


public:
    QGraphicsScene *scene;
    QGraphicsView *view;
    PieceManager *manager;
    bool released = true;
    QDrag *drag;
    int tempScoreAdd = 0;

    QString curId = "";

    jishi *shizhong;
    fen *fen1;
    QMediaPlayer *player1;

};

#endif // MAINWINDOW_H
