#include "fen.h"

fen::fen(QWidget *parent) : QWidget(parent)
{
    f_font.setFamily("Microsoft YaHei");
}
void fen::paintEvent(QPaintEvent *event)
{   int wi;
    int he;
    wi=this->width();
    he=this->height();
    //渐变
    QLinearGradient linear(QPointF(80, 80), QPointF(150, 150));
    linear.setColorAt(0, QColor(245,245,245));
    linear.setColorAt(1, QColor(160,82,45 ));
    // 设置显示模式
    linear.setSpread(QGradient::ReflectSpread);

    QPainter painter1(this);
    painter1.setRenderHint(QPainter::Antialiasing);
    // 设置画笔颜色、宽度
    painter1.setPen(QPen(linear, 40));
    // 设置画刷颜色
    painter1.setBrush(QColor(255, 255, 255));
    painter1.drawRect(0,0,wi,he);
    //分数显示
    f_font.setPixelSize(this->width()/8);
    painter1.setPen(QColor(8,46,84 ));
    painter1.setFont(f_font);
    painter1.drawText(this->rect(), Qt::AlignCenter, QString("score:%0").arg(QString::number(f_value)));

}
