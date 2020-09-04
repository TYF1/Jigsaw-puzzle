#ifndef JISHI_H
#define JISHI_H

#include <QWidget>
#include <QMainWindow>
#include <QObject>
#include <QPainter>
#include <QtMath>
#include <QMediaPlayer>
#include <QWidget>
#include <QMediaPlayer>

//计时器
class jishi : public QWidget
{
 public:
    jishi(QWidget *parent = 0);
    void setValue(int value) {m_value = value;}
    int value() {return m_value;}

    void setMaxValue(int value) {m_maxValue = value;}
    int maxValue() {return m_maxValue;}

    void setMinValue(int value) {m_minValue = value;}
    int minValue() {return m_minValue;}

    QColor m_usedColor = QColor(64,224,205 );
    QColor m_textColor = Qt::black;
    QColor m_boderColor =QColor(255,255,255);
    QColor m_bgColor = Qt::white;
    QColor m_boderColor1=QColor(255,192,203 );
protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);


private:
    QFont m_font;
    int m_value =60;
    int m_minValue = 0;
    int m_maxValue = 60;
    int m_waterDensity = 3; // 水波的密度
    double m_waterHeight = 0.05;
    double m_offset = 50;
    int m_borderWidth = 20;

};



#endif  // JISHI_H
