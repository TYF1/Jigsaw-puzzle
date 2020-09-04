#ifndef FEN_H
#define FEN_H

#include <QWidget>
#include <QWidget>

#include <QPainter>

#include <QtMath>

class fen : public QWidget
{
    Q_OBJECT
public:
    fen(QWidget *parent = nullptr);
    void setValue(int value) {f_value = value;}
    int value() {return f_value;}
protected:
    void paintEvent(QPaintEvent *event);

private:
    QFont f_font;
    int f_value=0;

public slots:
};

#endif // FEN_H
