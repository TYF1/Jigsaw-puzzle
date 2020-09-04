#include "jishi.h"

jishi::jishi(QWidget *parent) : QWidget(parent)
{
    m_font.setFamily("Microsoft YaHei");
    this->startTimer(200);
}



void jishi::paintEvent(QPaintEvent *event)

{

    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    int height = this->height();
    int width = this->width();
    int side = qMin(width, height);



    //计算当前值所占百分比

    double percent = 1 - (double)(m_value - m_minValue) / (m_maxValue - m_minValue);



    //正弦曲线公式 y = A * sin(ωx + φ) + k

    //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度

    double w = m_waterDensity * M_PI / width;

    //A表示振幅,可以理解为水波的高度,值越大高度越高(越浪 ^_^),取值高度的百分比

    double A = height * m_waterHeight;

    //k表示y轴偏移,可以理解为进度,取值高度的进度百分比

    double k = height * percent;



    //第一条波浪路径集合

    QPainterPath waterPath1;

    //第二条波浪路径集合

    QPainterPath waterPath2;



    //移动到左上角起始点

    waterPath1.moveTo(0, height);
    waterPath2.moveTo(0, height);



    m_offset += 0.6;
    if (m_offset > (width / 2)) {
        m_offset = 0;
    }


    for(int x = 0; x <= width; x++) {
        //第一条波浪Y轴
        double waterY1 = (double)(A * sin(w * x + m_offset)) + k;
        //第二条波浪Y轴
        double waterY2 = (double)(A * sin(w * x + m_offset + (width / 2 * w))) + k;
        //如果当前值为最小值则Y轴为高度
        if (m_value == m_minValue) {
            waterY1 = height;
            waterY2 = height;
        }



        //如果当前值为最大值则Y轴为0
        if (m_value == m_maxValue) {
            waterY1 = 0;
            waterY2 = 0;
        }
        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);
    }



    //移动到右下角结束点,整体形成一个闭合路径
    waterPath1.lineTo(width, height);
    waterPath2.lineTo(width, height);



    //渐变
    QLinearGradient linear(QPointF(80, 80), QPointF(150, 150));
    linear.setColorAt(0, m_boderColor1);
    linear.setColorAt(1, m_boderColor);

    // 设置显示模式
    linear.setSpread(QGradient::ReflectSpread );


    //大路径

    QPainterPath bigPath;
    //底层大圆，周边
    painter.setBrush(linear);
    painter.setPen(QColor(0,0,0));
    painter.drawEllipse((width - side)/2, (height - side)/2, side*2, height*2);
    painter.drawEllipse((width - side) / 2, (height - side) / 2, side, height);
    //中间圆
    side = side - m_borderWidth*2;
    bigPath.addEllipse((width - side) / 2, m_borderWidth, side, side);
    //第二层
    painter.setBrush(QColor(192,192,192 ));
    painter.setPen(QColor(0,0,0));
    painter.drawEllipse((width - side) / 2-4, m_borderWidth-4, side+8, side+8);
    //背景
    painter.setBrush(m_bgColor);
    painter.setPen(QColor(0,0,0));
    painter.drawEllipse((width - side) / 2, m_borderWidth, side, side);

    painter.save();




    //新路径,用大路径减去波浪区域的路径,形成遮罩效果

    QPainterPath path;
    painter.setPen(Qt::NoPen);
    QColor waterColor1 = m_usedColor;
    waterColor1.setAlpha(100);
    QColor waterColor2 = m_usedColor;
    waterColor2.setAlpha(180);



    //第一条波浪挖去后的路径

    path = bigPath.intersected(waterPath1);
    painter.setBrush(waterColor1);
    painter.drawPath(path);



    //第二条波浪挖去后的路径
    path = bigPath.intersected(waterPath2);
    painter.setBrush(waterColor2);
    painter.drawPath(path);
    painter.restore();



    //绘制文字

    m_font.setPixelSize(this->width()/4);
    painter.setPen(m_textColor);
    painter.setFont(m_font);
    painter.drawText(this->rect(), Qt::AlignCenter, QString("%0s").arg(QString::number(m_value)));

}



void jishi::timerEvent(QTimerEvent *event)

{
    Q_UNUSED(event);
    this->update();

}

