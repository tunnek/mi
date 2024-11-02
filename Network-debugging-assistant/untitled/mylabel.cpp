#include "mylabel.h"

#include <QMouseEvent>

myLabel::myLabel(QWidget *parent): QLabel(parent)
{

}

void myLabel::mousePressEvent(QMouseEvent *ev)
{
    //如果是鼠标左键发送信号
    if(ev->button() == Qt::LeftButton){
        emit clicked();
    }

    QLabel::mousePressEvent(ev);
}
