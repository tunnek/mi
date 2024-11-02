#include "mybtnopen.h"
#include <QPainter>
#include <QMouseEvent>

myBtnOpen::myBtnOpen(QWidget *parent):QPushButton(parent)
{
    // 加载初始图片
    pic.load(":/pictures/mm.png");
    // 设置按钮的固定大小为图片的大小
    //setFixedSize(pic.size());
    //setFixedSize(100,100);
    // 刷新界面，触发 paintEvent 进行绘制
    update();
}

void myBtnOpen::paintEvent(QPaintEvent *e)
{
    // 创建一个 QPainter 对象，负责绘制图片
    QPainter painter(this);
    // 使用 QPainter 在按钮区域内绘制当前加载的图片
    painter.drawPixmap(rect(), pic);
}

void myBtnOpen::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        //打开
        if(t == true){

            pic.load(":/pictures/mm.png");
            update();
            t = false;
        }else{
            pic.load(":/pictures/pp.png");
            update();
            t = true;
        }
    }
    QPushButton::mousePressEvent(e);
}
