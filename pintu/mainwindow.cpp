#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QIcon>
#include <QPushButton>
#include <QMediaPlayer>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QTableView>
#include "game.h"
#include <QInputDialog>
#include<QPixmap>
#include<QLabel>
#include<QSlider>
#include <QGraphicsScene>
#include <QGraphicsView>
#include<QSpinBox>
#include<QLineEdit>
#include<QDirModel>



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jishi.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    scene(new QGraphicsScene(0, 0, SceneWidth, SceneHeight)),
    view(new QGraphicsView(scene)),
    manager(new PieceManager(scene, this)),
    ui(new Ui::MainWindow)
{
    setWindowTitle(tr("兆聪拼图"));
    QWidget* w = new QWidget();
    printer  =new QLabel(this);
    this->setCentralWidget(w);

    dialog1.setWindowTitle(tr("volume"));
    dialog1.setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    dialog1.setFixedHeight(50);
    dialog1.setFixedWidth(350);   //设置音量调节的子窗口
    dialog2.setWindowTitle(tr("BGM"));
    dialog2.setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    dialog2.setFixedHeight(450);
    dialog2.setFixedWidth(310);   //设置更改BGM的子窗口
    slider = new QSlider(Qt::Horizontal,this);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setValue(10);
    slider->setParent(&dialog1);
    slider->setGeometry(0,0,350,50);//设置音量滑动条
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changevolume(int)));//连接滑动条与改变音量的函数
    Mplaylist  = new QMediaPlaylist;
    Mplayers =new QMediaPlayer;//初始化播放器与播放列表
    Mplaylist->addMedia(QUrl::fromLocalFile("music/1.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/2.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/3.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/4.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/5.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/6.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/7.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/8.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/9.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/10.wma"));
    Mplaylist->addMedia(QUrl::fromLocalFile("music/11.wma"));   //添加音乐
    Mplaylist->setPlaybackMode(QMediaPlaylist::Loop);
    Mplayers->setPlaylist(Mplaylist);    //设置播放属性
    model = new QStandardItemModel(11,1);
    model->setHeaderData(0,Qt::Horizontal,tr("MUSIC"));
    views  = new QTableView();
    views->setModel(model);//创建表格
    btn1 =new QPushButton(QString::fromUtf8("Summer—久石让"));
    btn1->setObjectName("1");
    btn2= new QPushButton("Granpa's Little Train Song-MARTY");
    btn2->setObjectName("2");
    btn3 =new QPushButton(QString::fromUtf8("学猫叫—小潘潘"));
    btn3->setObjectName("3");
    btn4= new QPushButton("…And Overwatch for All-Sam Cardon");
    btn4->setObjectName("4");
    btn5 =new QPushButton("Tavern-World Of Warcraft");
    btn5->setObjectName("5");
    btn6= new QPushButton(QString::fromUtf8("猴哥——张伟进"));
    btn6->setObjectName("6");
    btn7 =new QPushButton("STAR-Richard Clayderman");
    btn7->setObjectName("7");
    btn8= new QPushButton("Invincible-Russell Brower");
    btn8->setObjectName("8");
    btn9= new QPushButton("Warcraft Suite-Various Artists");
    btn9->setObjectName("9");
    btn10= new QPushButton("Pull up a Chair-Peter McConnell");
    btn10->setObjectName("10");
    btn11= new QPushButton("Wave Rider-Ti_sto");
    btn11->setObjectName("11");//设置播放列表
    views->setIndexWidget(model->index(0,0),btn1);
    views->setIndexWidget(model->index(1,0),btn2);
    views->setIndexWidget(model->index(2,0),btn3);
    views->setIndexWidget(model->index(3,0),btn4);
    views->setIndexWidget(model->index(4,0),btn5);
    views->setIndexWidget(model->index(5,0),btn6);
    views->setIndexWidget(model->index(6,0),btn7);
    views->setIndexWidget(model->index(7,0),btn8);
    views->setIndexWidget(model->index(8,0),btn9);
    views->setIndexWidget(model->index(9,0),btn10);
    views->setIndexWidget(model->index(10,0),btn11);//添加播放列表
    views->resize(310,450);
    views->resizeColumnsToContents();
    views->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    views->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    views->horizontalHeader()->setMinimumSectionSize(100);    //设置表格属性
    connect(btn1,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn2,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn3,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn4,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn5,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn6,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn7,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn8,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn9,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn10,SIGNAL(clicked()),this,SLOT(musicplay()));
    connect(btn11,SIGNAL(clicked()),this,SLOT(musicplay()));//连接表中歌曲与播放函数
    views->setParent(&dialog2);
    Mplayers->play();//开始播放
    changevolume(slider->value());//更改音量

    //设置菜单栏下拉菜单内容
    playAction = new QAction(tr("Play"), this);
    quitAction = new QAction(tr("quit"),this);
    instAction = new QAction(tr("Instruction"),this);
    CbgmAction = new QAction(tr("Change BGM"),this);
    voluAction = new QAction(tr("BGM Volume"),this);
    voluAction = new QAction(tr("Volume"),this);
    rankAction = new QAction(tr("ranking list"),this);

    //设置状态栏
    playAction->setStatusTip(tr("Play the game"));
    quitAction->setStatusTip(tr("Quit the game"));
    instAction->setStatusTip(tr("Read the instruction"));
    CbgmAction->setStatusTip(tr("Change your BGM"));
    voluAction->setStatusTip(tr("Change the volume of BGM"));
    rankAction->setStatusTip(tr("Check the ranking list"));


    //创建菜单栏
    QMenu *Start = menuBar()->addMenu(tr("Start"));
    QMenu *Check = menuBar()->addMenu(tr("Check"));
    QMenu *Settings = menuBar()->addMenu(tr("Settings"));

    //添加菜单栏具体功能
    Start->addAction(playAction);
    Start->addAction(quitAction);
    Check->addAction(instAction);
    Check->addAction(rankAction);
    Settings->addAction(CbgmAction);
    Settings->addAction(voluAction);

    //设置信号槽实现菜单部分功能
    connect(instAction,&QAction::triggered,this,&MainWindow::inst);
    connect(voluAction,&QAction::triggered,this,&MainWindow::volumedialog);
    connect(CbgmAction,&QAction::triggered,this,&MainWindow::playerlist);
    connect(quitAction,&QAction::triggered,this,&MainWindow::quit);

    //添加状态栏
    statusBar() ;


    //固定窗口大小
    this->setMaximumSize(QSize(1920,1080));
    this->setMinimumSize(QSize(1920,1080));

    //设置UI界面背景
    this->autoFillBackground();
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap("./images/beijin.png")));
    this->setPalette(palette);

    //开始游戏按钮
    startBtn = new QPushButton(this);
    startBtn->setStyleSheet("QPushButton{ border-image:url(./images/anniun2.png);}""QPushButton:hover{ border-image:url(./images/anniu3.png);}");
    startBtn->setGeometry(QRect(600,550,300,180));


    //排行榜按钮
    rankBtn = new QPushButton(this);
    rankBtn->setStyleSheet("QPushButton{ border-image:url(./images/rank.png);}""QPushButton:hover{ border-image:url(./images/rank1.png);}");
    rankBtn->setGeometry(QRect(650,800,100,100));

    //退出游戏按钮
    quitBtn = new QPushButton(this);
    quitBtn->setStyleSheet("QPushButton{ border-image:url(./images/quit.png);}""QPushButton:hover{ border-image:url(./images/quit1.png);}");
    quitBtn->setGeometry(QRect(1850,50,50,50));
    connect(quitBtn,&QPushButton::clicked,this,&MainWindow::quit);

    //难度选择按钮
    jiandan = new QPushButton(this);
    zhongdeng = new QPushButton(this);
    kunnan = new QPushButton(this);
    emeng = new QPushButton(this);
    diyu = new QPushButton(this);
    jiandan->setGeometry(QRect(600,450,150,75));
    zhongdeng->setGeometry(QRect(600,550,150,75));
    kunnan->setGeometry(QRect(600,650,150,75));
    emeng->setGeometry(QRect(600,750,150,75));
    diyu->setGeometry(QRect(600,850,150,75));
    jiandan->setStyleSheet("QPushButton{ border-image:url(./images/a2.png);}""QPushButton:hover{ border-image:url(./images/a1.png);}");
    zhongdeng->setStyleSheet("QPushButton{ border-image:url(./images/b2.png);}""QPushButton:hover{ border-image:url(./images/b1.png);}");
    kunnan->setStyleSheet("QPushButton{ border-image:url(./images/c2.png);}""QPushButton:hover{ border-image:url(./images/c1.png);}");
    emeng->setStyleSheet("QPushButton{ border-image:url(./images/d2.png);}""QPushButton:hover{ border-image:url(./images/d1.png);}");
    diyu->setStyleSheet("QPushButton{ border-image:url(./images/e1.png);}""QPushButton:hover{ border-image:url(./images/e2.png);}");
    jiandan->hide();
    zhongdeng->hide();
    kunnan->hide();
    emeng->hide();
    diyu->hide();

    //返回主菜单按钮
    backBtn = new QPushButton(this);
    backBtn->setGeometry(QRect(20,950,150,150));
    backBtn->setStyleSheet("QPushButton{ border-image:url(./images/return.png);}""QPushButton:hover{ border-image:url(./images/return1.png);}");
    backBtn->hide();

    //返回主菜单按钮for游戏中
    backBtn2 = new QPushButton(this);
    backBtn2->setGeometry(QRect(20,950,150,150));
    backBtn2->setStyleSheet("QPushButton{ border-image:url(./images/return.png);}""QPushButton:hover{ border-image:url(./images/return1.png);}");
    backBtn2->hide();



    //开始游戏按钮及菜单相应选项事件
    connect(startBtn,SIGNAL(clicked(bool)),startBtn,SLOT(hide()));
    connect(startBtn,SIGNAL(clicked(bool)),rankBtn,SLOT(hide()));
    connect(playAction,&QAction::triggered,startBtn,&QPushButton::hide);
    connect(playAction,&QAction::triggered,rankBtn,&QPushButton::hide);

    connect(startBtn,SIGNAL(clicked(bool)),jiandan,SLOT(show()));
    connect(startBtn,SIGNAL(clicked(bool)),zhongdeng,SLOT(show()));
    connect(startBtn,SIGNAL(clicked(bool)),kunnan,SLOT(show()));
    connect(startBtn,SIGNAL(clicked(bool)),emeng,SLOT(show()));
    connect(startBtn,SIGNAL(clicked(bool)),diyu,SLOT(show()));
    connect(startBtn,SIGNAL(clicked(bool)),backBtn,SLOT(show()));
    connect(playAction,&QAction::triggered,jiandan,&QPushButton::show);
    connect(playAction,&QAction::triggered,zhongdeng,&QPushButton::show);
    connect(playAction,&QAction::triggered,kunnan,&QPushButton::show);
    connect(playAction,&QAction::triggered,emeng,&QPushButton::show);
    connect(playAction,&QAction::triggered,diyu,&QPushButton::show);
    connect(playAction,&QAction::triggered,backBtn,&QPushButton::show);

    //难度选择按钮事件
    connect(jiandan,SIGNAL(clicked(bool)),jiandan,SLOT(hide()));
    connect(jiandan,SIGNAL(clicked(bool)),zhongdeng,SLOT(hide()));
    connect(jiandan,SIGNAL(clicked(bool)),kunnan,SLOT(hide()));
    connect(jiandan,SIGNAL(clicked(bool)),emeng,SLOT(hide()));
    connect(jiandan,SIGNAL(clicked(bool)),diyu,SLOT(hide()));

    connect(zhongdeng,SIGNAL(clicked(bool)),jiandan,SLOT(hide()));
    connect(zhongdeng,SIGNAL(clicked(bool)),zhongdeng,SLOT(hide()));
    connect(zhongdeng,SIGNAL(clicked(bool)),kunnan,SLOT(hide()));
    connect(zhongdeng,SIGNAL(clicked(bool)),emeng,SLOT(hide()));
    connect(zhongdeng,SIGNAL(clicked(bool)),diyu,SLOT(hide()));

    connect(kunnan,SIGNAL(clicked(bool)),jiandan,SLOT(hide()));
    connect(kunnan,SIGNAL(clicked(bool)),zhongdeng,SLOT(hide()));
    connect(kunnan,SIGNAL(clicked(bool)),kunnan,SLOT(hide()));
    connect(kunnan,SIGNAL(clicked(bool)),emeng,SLOT(hide()));
    connect(kunnan,SIGNAL(clicked(bool)),diyu,SLOT(hide()));

    connect(emeng,SIGNAL(clicked(bool)),jiandan,SLOT(hide()));
    connect(emeng,SIGNAL(clicked(bool)),zhongdeng,SLOT(hide()));
    connect(emeng,SIGNAL(clicked(bool)),kunnan,SLOT(hide()));
    connect(emeng,SIGNAL(clicked(bool)),emeng,SLOT(hide()));
    connect(emeng,SIGNAL(clicked(bool)),diyu,SLOT(hide()));

    connect(diyu,SIGNAL(clicked(bool)),jiandan,SLOT(hide()));
    connect(diyu,SIGNAL(clicked(bool)),zhongdeng,SLOT(hide()));
    connect(diyu,SIGNAL(clicked(bool)),kunnan,SLOT(hide()));
    connect(diyu,SIGNAL(clicked(bool)),emeng,SLOT(hide()));
    connect(diyu,SIGNAL(clicked(bool)),diyu,SLOT(hide()));

    connect(jiandan,SIGNAL(clicked(bool)),backBtn,SLOT(hide()));
    connect(zhongdeng,SIGNAL(clicked(bool)),backBtn,SLOT(hide()));
    connect(kunnan,SIGNAL(clicked(bool)),backBtn,SLOT(hide()));
    connect(emeng,SIGNAL(clicked(bool)),backBtn,SLOT(hide()));
    connect(diyu,SIGNAL(clicked(bool)),backBtn,SLOT(hide()));

    connect(jiandan,SIGNAL(clicked(bool)),backBtn2,SLOT(show()));
    connect(zhongdeng,SIGNAL(clicked(bool)),backBtn2,SLOT(show()));
    connect(kunnan,SIGNAL(clicked(bool)),backBtn2,SLOT(show()));
    connect(emeng,SIGNAL(clicked(bool)),backBtn2,SLOT(show()));
    connect(diyu,SIGNAL(clicked(bool)),backBtn2,SLOT(show()));

    connect(jiandan,&QPushButton::clicked,this, &MainWindow::gamej);
    connect(zhongdeng,&QPushButton::clicked,this, &MainWindow::gamez);
    connect(kunnan,&QPushButton::clicked,this, &MainWindow::gamek);
    connect(emeng,&QPushButton::clicked,this, &MainWindow::gamee);
    connect(diyu,&QPushButton::clicked,this, &MainWindow::gamed);

    //排行榜按钮事件
    connect(rankBtn,&QPushButton::clicked,this,&MainWindow::rankList);
    connect(rankAction,&QAction::triggered,this,&MainWindow::rankList);

    //返回按钮事件
    connect(backBtn,SIGNAL(clicked(bool)),jiandan,SLOT(hide()));
    connect(backBtn,SIGNAL(clicked(bool)),zhongdeng,SLOT(hide()));
    connect(backBtn,SIGNAL(clicked(bool)),kunnan,SLOT(hide()));
    connect(backBtn,SIGNAL(clicked(bool)),emeng,SLOT(hide()));
    connect(backBtn,SIGNAL(clicked(bool)),diyu,SLOT(hide()));
    connect(backBtn,SIGNAL(clicked(bool)),startBtn,SLOT(show()));
    connect(backBtn,SIGNAL(clicked(bool)),rankBtn,SLOT(show()));
    connect(backBtn,SIGNAL(clicked(bool)),backBtn,SLOT(hide()));


    //返回按钮事件for游戏中
    connect(backBtn2,SIGNAL(clicked(bool)),startBtn,SLOT(show()));
    connect(backBtn2,SIGNAL(clicked(bool)),rankBtn,SLOT(show()));
    connect(backBtn2,SIGNAL(clicked(bool)),view,SLOT(hide()));
    connect(backBtn2,SIGNAL(clicked(bool)),backBtn2,SLOT(hide()));
    connect(backBtn2,&QPushButton::clicked,this,&MainWindow::changeM);   
    connect(backBtn2,&QPushButton::clicked,this,&MainWindow::interUsername);
    connect(backBtn2,&QPushButton::clicked,this,&MainWindow::xiao);
    connect(backBtn2,SIGNAL(clicked(bool)),this,SLOT(clear()));
    connect(backBtn2,SIGNAL(clicked(bool)),this,SLOT(playbackmode()));

    //计时器
    shizhong=new jishi(this);
    shizhong->setGeometry(QRect(this->width()-165,this->height()-165,165,165));
    shizhong->hide();
    //时间信号
    timer1 = new QTimer(this);
    timer1 -> setInterval(1000);
    connect(timer1,&QTimer::timeout,this,&MainWindow::update1);
    //计时器音乐播放
    player1=new QMediaPlayer;
    player1->setMedia(QUrl::fromLocalFile("./images/qtee.mp3"));
    player1->setVolume(400);
    //分数显示框
    fen1=new fen(this);
    fen1->setGeometry(QRect(this->width()-600,this->height()-120,400,100));
    fen1->hide();

    //游戏全屏
    showFullScreen();

    for(int i = 1; i <= 13; i++) {
        this->levelScore[i] = 0;
    }

}


//游戏说明实现函数
void MainWindow::inst()
{
    QMessageBox instruction;
    instruction.information(this,tr("Instruction of the game"),"Finish the image with those pieces. How can you not know how to play this easy game??",QMessageBox::Ok,QMessageBox::NoButton);
}

//游戏结束实现函数
void MainWindow::quit()
{
    if(QMessageBox::Yes == QMessageBox::question(this,tr("Quit the game"),tr("Do you want to quit the game?"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes))
    {
        QApplication::exit();
    }

}


//变换鼠标图标
void MainWindow::changeM(){
    setCursor(Qt::ArrowCursor);
}

void MainWindow::addUpScore() {
    int tmp = 0;
    for(auto i = this->levelScore.begin(); i != this->levelScore.end(); i++) {
        tmp += i->second;
    }
    this->score = tmp;
}

//简单难度
void MainWindow::gamej() {
    fen1->show();
    timer1->start();
    shizhong->m_usedColor = QColor(64,224,205 );
    shizhong->m_textColor = Qt::black;
    shizhong->m_boderColor =QColor(255,255,255);
    shizhong->m_bgColor = Qt::white;
    shizhong->m_boderColor1=QColor(255,192,203 );


    this->manager->flushManager();
    
    if(this->level > 3)
        this->level = 1;

    scene->setParent(this);

    setCursor(Qt::OpenHandCursor);
    srand((int)GetTickCount());
    Blank *blank = new Blank(manager);
    scene->addItem(blank);

    if(this->level == 1)
    {   Mplayers->stop();
        Mplaylist->setCurrentIndex(1);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(30);
        shizhong->setValue(30);
        shizhong->show();
        SubGame("peppa", "peppa.jpg", 3, manager);
       QPixmap levelimg("./images/l1.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();
    }
    else if(this->level == 2)
    {
        //时间设定
        shizhong->setMaxValue(30);
        shizhong->setValue(30);
        shizhong->show();
        SubGame("beef", "beef.jpg", 3, manager);
         printer->clear();
        QPixmap levelimg("./images/l2.png");
         printer->setPixmap(levelimg);
         printer->setGeometry(100,900,391,190);
         printer->show();
                   }
    else if(this->level == 3)
    {
        //时间设定
        shizhong->setMaxValue(45);
        shizhong->setValue(45);
        shizhong->show();
        SubGame("starry", "starry.jpg", 3, manager);
        printer->clear();
       QPixmap levelimg("./images/l3.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();}
    else if(this->level == 4) {
        this->view->hide();
        return;
    }

    //view = new QGraphicsView(scene, this);
    view->resize(ViewWidth, ViewHeight);
    view->setParent(this);
    view->move(ViewMarginLeft, ViewMarginTop);
    view->show();
}

//中等难度
void MainWindow::gamez() {
    timer1->start();
    fen1->show();
    shizhong->m_usedColor = QColor(64,224,205 );
    shizhong->m_textColor = Qt::black;
    shizhong->m_boderColor =QColor(255,255,255);
    shizhong->m_bgColor = Qt::white;
    shizhong->m_boderColor1=QColor(255,192,203 );


    this->manager->flushManager();

    if(this->level < 4 || this->level > 6)
        this->level = 4;

    scene->setParent(this);

    setCursor(Qt::OpenHandCursor);
    srand((int)GetTickCount());
    Blank *blank = new Blank(manager);
    scene->addItem(blank);

    if(this->level == 4)
    {   Mplayers->stop();
        Mplaylist->setCurrentIndex(2);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(60);
        shizhong->setValue(60);
        shizhong->show();
        SubGame("cat", "cat.jpg", 4, manager);
        printer->clear();
       QPixmap levelimg("./images/l4.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();
    }
    else if(this->level == 5)
    {   Mplayers->stop();
        Mplaylist->setCurrentIndex(3);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(75);
        shizhong->setValue(75);
        shizhong->show();
        SubGame("black", "black.jpg", 4, manager);
        printer->clear();
       QPixmap levelimg("./images/l5.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();}
    else if(this->level == 6)
    {   Mplayers->stop();
        Mplaylist->setCurrentIndex(4);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(90);
        shizhong->setValue(90);
        shizhong->show();
        SubGame("wow8", "wow8.jpg", 4, manager);
        printer->clear();
       QPixmap levelimg("./images/l6.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();}
    else if(this->level == 7) {
        this->view->hide();
        return;
    }

    //view = new QGraphicsView(scene, this);
    view->resize(ViewWidth, ViewHeight);
    view->setParent(this);
    view->move(ViewMarginLeft, ViewMarginTop);
    view->show();
}

//困难难度
void MainWindow::gamek() {
    fen1->show();
    timer1->start();
    shizhong->m_usedColor = QColor(64,224,205 );
    shizhong->m_textColor = Qt::black;
    shizhong->m_boderColor =QColor(255,255,255);
    shizhong->m_bgColor = Qt::white;
    shizhong->m_boderColor1=QColor(255,192,203 );


    this->manager->flushManager();

    if(this->level < 7 || this->level > 9)
        this->level = 7;

    scene->setParent(this);

    setCursor(Qt::OpenHandCursor);
    srand((int)GetTickCount());
    Blank *blank = new Blank(manager);
    scene->addItem(blank);

    if(this->level == 7)
    {   Mplayers->stop();
        Mplaylist->setCurrentIndex(5);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(110);
        shizhong->setValue(110);
        shizhong->show();
        SubGame("monkey", "monkey.jpg", 5, manager);
        printer->clear();
        QPixmap levelimg("./images/l7.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();}
    else if(this->level == 8)
    {   Mplayers->stop();
        Mplaylist->setCurrentIndex(3);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(130);
        shizhong->setValue(130);
        shizhong->show();
        SubGame("hanzo", "hanzo.jpg", 5, manager);
        printer->clear();
        QPixmap levelimg("./images/l8.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();}
    else if(this->level == 9) {
        Mplayers->stop();
        Mplaylist->setCurrentIndex(7);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(150);
        shizhong->setValue(150);
        shizhong->show();
        SubGame("lich", "lich.jpg", 5, manager);
        printer->clear();
        QPixmap levelimg("./images/l9.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();
    }
    else if(this->level == 10) {
        this->view->hide();
        return;
    }

    //view = new QGraphicsView(scene, this);
    view->resize(ViewWidth, ViewHeight);
    view->setParent(this);
    view->move(ViewMarginLeft, ViewMarginTop);
    view->show();
}

//噩梦难度
void MainWindow::gamee() {
    fen1->show();
    timer1->start();
    shizhong->m_usedColor = QColor(64,224,205 );
    shizhong->m_textColor = Qt::black;
    shizhong->m_boderColor =QColor(255,255,255);
    shizhong->m_bgColor = Qt::white;
    shizhong->m_boderColor1=QColor(255,192,203 );

    this->manager->flushManager();

    if(this->level < 10 || this->level > 12)
        this->level = 10;

    scene->setParent(this);

    setCursor(Qt::OpenHandCursor);
    srand((int)GetTickCount());
    Blank *blank = new Blank(manager);
    scene->addItem(blank);

    if(this->level == 10)
    {   Mplayers->stop();
        Mplaylist->setCurrentIndex(6);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(195);
        shizhong->setValue(195);
        shizhong->show();
        SubGame("vstarry", "vstarry.jpg", 4, manager);
        printer->clear();
        QPixmap levelimg("./images/l10.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();
    }
    else if(this->level == 11)
    {    Mplayers->stop();
        Mplaylist->setCurrentIndex(8);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(250);
        shizhong->setValue(250);
        shizhong->show();
        SubGame("illidan", "illidan.jpg", 6, manager);
        printer->clear();
        QPixmap levelimg("./images/l11.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();}
    else if(this->level == 12)
    {   Mplayers->stop();
        Mplaylist->setCurrentIndex(9);
        Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        Mplayers->play();
        //时间设定
        shizhong->setMaxValue(500);
        shizhong->setValue(500);
        shizhong->show();
        SubGame("hearthstone", "hearthstone.jpg", 10, manager);
        printer->clear();
        QPixmap levelimg("./images/l12.png");
        printer->setPixmap(levelimg);
        printer->setGeometry(100,900,391,190);
        printer->show();}
    else if(this->level == 13) {
        printer->show();
        this->view->hide();
        return;
    }

    //view = new QGraphicsView(scene, this);
    view->resize(ViewWidth, ViewHeight);
    view->setParent(this);
    view->move(ViewMarginLeft, ViewMarginTop);
    view->show();
}

//地狱难度
void MainWindow::gamed() {
    //时间设定
    shizhong->setMaxValue(1800);
    shizhong->setValue(1800);
    shizhong->show();
    fen1->show();
    timer1->start();
    shizhong->m_usedColor = QColor(64,224,205 );
    shizhong->m_textColor = Qt::black;
    shizhong->m_boderColor =QColor(255,255,255);
    shizhong->m_bgColor = Qt::white;
    shizhong->m_boderColor1=QColor(255,192,203 );

    this->manager->flushManager();

    if(this->level != 13)
        this->level = 13;

    scene->setParent(this);

    setCursor(Qt::OpenHandCursor);
    srand((int)GetTickCount());
    Blank *blank = new Blank(manager);
    scene->addItem(blank);

    SubGame("subway", "subway.jpg", 10, manager);
    Mplayers->stop();
    Mplaylist->setCurrentIndex(10);
    Mplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    Mplayers->play();
    printer->clear();
   QPixmap levelimg("./images/l13.png");
    printer->setPixmap(levelimg);
    printer->setGeometry(100,900,391,190);
    printer->show();

    //view = new QGraphicsView(scene, this);
    view->resize(ViewWidth, ViewHeight);
    view->setParent(this);
    view->move(ViewMarginLeft, ViewMarginTop);
    view->show();
}

//向文件中写入分数
void MainWindow::writeScore(QString playerName)
{
    QFile file("./playerdata/"+playerName+".txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << score << endl;
    }
    score = 0;
    file.close();
    return ;
}

//向文件中写入姓名
void MainWindow::namelist(QString playName)
{
    QFile file("namelist.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << playName << endl;
    }
}

//排行榜实现
void MainWindow::rankList()
{
    int i = 0;
    int scores[100];
    QFile file1("namelist.txt");
    if(file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       while(!file1.atEnd())
       {
          QByteArray line = file1.readLine();
          QString str(line);
          str = str.section('\n',0,0);

          name1.insert(str);
       }
    }
    QList<QString> name = name1.toList();
    while(i < name.count())
    {
            QFile file("./playerdata/"+name.at(i)+".txt");
            if(file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                int count = 0;
                while(!file.atEnd())
                {
                    QByteArray line = file.readLine();
                    QString str(line);
                    str = str.section('\n',0,0);
                    scores[count] = str.toInt();
                    count++;
                }
                for(int j = 0 ; j < count ; j++)
                {
                    for(int a = j+1 ; a < count ; a++)
                    {
                        if(scores[j] < scores[a])
                        {
                            int temp;
                            temp = scores[j];
                            scores[j] = scores[a];
                            scores[a] = temp;
                        }
                    }
                }
                scores1.append(scores[0]);
            }
            i++;
    }
    for(int j = 0 ; j < name.count() ; j++)
    {
        for(int a = j+1 ; a < name.count() ; a++)
        {
            if(scores1.at(j) < scores1.at(a))
            {
                 scores1.swap(j,a);
                 name.swap(j,a);
            }
        }
    }
    QDialog rankingList(this);
    rankingList.resize(275, 300);
    rankingList.setMaximumSize(275, 300);
    QStandardItemModel model(10,2);
    QTableView tableView;
    tableView.resize(274, 300);
    tableView.setParent(&rankingList);
    tableView.setModel(&model);
    model.setHeaderData(0,Qt::Horizontal,QObject::tr("Name"));
    model.setHeaderData(1,Qt::Horizontal,QObject::tr("Score"));
    int row = 0;
    if(name.count()>=10)
    {
        for(int i = 0;i < 10;i++)
        {
            model.setData(model.index(row,0,QModelIndex()),name.at(i));
            model.setData(model.index(row,1,QModelIndex()),scores1.at(i));
            row++;
        }
    }
    else
    {
        for(int i = 0;i < name.count();i++)
        {
            model.setData(model.index(row,0,QModelIndex()),name.at(i));
            model.setData(model.index(row,1,QModelIndex()),scores1.at(i));
            row++;
        }
    }
    rankingList.setWindowTitle(tr("Ranking List"));
    tableView.show();
    rankingList.exec();
    name.clear();
    scores1.clear();
}

QString Strip(QString str) {
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == ' ') {
            str.remove(i, 1);
        }
    }
    return str;
}

//玩家输入用户名
void MainWindow::interUsername()
{
    fen1->hide();
    shizhong->hide();
    if(score == 0)
        return;
    bool isOK1 = true;
    QString id;
    int confirmed = 0;
    if(this->curId == "") {
        confirmed = 1;
    } else {
        confirmed = 2;
    }
    if(confirmed == 1) {
        if (QMessageBox::Yes == QMessageBox::question(this,
                                                      "Zhao Cong Puzzle",
                                                      "Do you want to enter your ID?",
                                                      QMessageBox::Yes | QMessageBox::No))
         {
         getId:
            id = QInputDialog::getText(this,"Zhao Cong Puzzle",
                                               "enter your ID",
                                               QLineEdit::Normal,
                                               "player",&isOK1);
            if(Strip(id).isEmpty())
            {
                QMessageBox::warning(this, "Zhao Cong Puzzle", "you should enter somthing");
                goto getId;
            }
            namelist(id);
         }
        else
        {
           isOK1 = false;
        }
        if(isOK1)
        {
            QMessageBox::information(this, "Zhao Cong Puzzle",
                                          "your ID is: <b>" + id + "</b>",
                                           QMessageBox::Yes | QMessageBox::No,
                                           (QMessageBox::Yes));
            this->curId = id;
            writeScore(id);
        }
        else
        {
           QMessageBox::warning(this,"Zhao Cong Puzzle","your game's datas will not save");
           return;
        }
    } else {
        writeScore(this->curId);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update1()
{
    if(a<=10){
        player1->play();
    }

    a = shizhong->value();
    a--;
    shizhong->setValue(a);

    if(a ==10){
        shizhong->m_textColor = Qt::white;
        shizhong->m_boderColor =Qt::black;
        shizhong->m_boderColor1 = QColor(116,0,0 );
        shizhong->m_bgColor = Qt::black;
    }
    if(a == 0) {
        if(this->manager->tempScoreAdd > this->levelScore.find(this->level)->second)
            this->levelScore[this->level] = this->manager->tempScoreAdd;
        this->addUpScore();
        timer1->stop();
        this->fen1->setValue(this->score);
        if(released) {
            int to;
            to = QMessageBox::warning(NULL,"Zhao Cong Puzzle","timeout!",QMessageBox::Ok);
            if(to == QMessageBox::Ok){
                backBtn2->click();
                shizhong->m_textColor =Qt::black;
                shizhong->m_boderColor =QColor(54, 54, 54);;
                shizhong->m_bgColor =Qt::white;
                shizhong->m_usedColor=QColor(0,245,255);
            }
        }
    }
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_P)//判断键值，此处以S键为例
              {
                  timer1->stop();
                  int reply;
                  reply = QMessageBox::question(NULL, "Zhao Cong Puzzle", "Paused. Click \"Yes\" to continue.", QMessageBox::Yes);
                  if(reply == QMessageBox::Yes){
                      /*shizhong->m_textColor = Qt::black;

                      shizhong->m_boderColor = Qt::black;

                      shizhong->m_bgColor = Qt::white;*/
                      timer1->start();

                  }
              }

}
//时钟消除
void MainWindow::xiao()
{
    shizhong->hide();
    timer1->stop();
    fen1->hide();
    shizhong->m_usedColor = QColor(64,224,205 );
    shizhong->m_textColor = Qt::black;
    shizhong->m_boderColor =QColor(255,255,255);
    shizhong->m_bgColor = Qt::white;
    shizhong->m_boderColor1=QColor(255,192,203 );
}
void MainWindow::clear(){
    printer->clear();
}
void MainWindow::changevolume(int n)
{
     Mplayers->setVolume(n);
}
void MainWindow::volumedialog()
{
    dialog1.exec();
}
void MainWindow::playerlist()
{

    dialog2.exec();
}
void MainWindow::musicplay()
{  QString get =this->sender()->objectName();
    if("1" == get)
    {Mplaylist->setCurrentIndex(0);}
    else if("2"==get)
    {Mplaylist->setCurrentIndex(1); }
    else if("3"==get)
    {Mplaylist->setCurrentIndex(2);}
    else if("4"==get)
    {Mplaylist->setCurrentIndex(3);}
    else if("5"==get)
    {Mplaylist->setCurrentIndex(4);  }
    else if("6"==get)
    {Mplaylist->setCurrentIndex(5);   }
    else if("7"==get)
    {Mplaylist->setCurrentIndex(6); }
    else if("8"==get)
    {Mplaylist->setCurrentIndex(7); }
    else if("9"==get)
    {Mplaylist->setCurrentIndex(8); }
    else if("10"==get)
    {Mplaylist->setCurrentIndex(9);}
    else if("11"==get)
    {Mplaylist->setCurrentIndex(10);}
    Mplayers->play();
}
void MainWindow::playbackmode()
{
    Mplaylist->setPlaybackMode(QMediaPlaylist::Loop);
}
