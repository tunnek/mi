#ifndef MYBTNOPEN_H
#define MYBTNOPEN_H

#include <QObject>
#include <QPushButton>
#include <QWidget>

class myBtnOpen : public QPushButton
{
    Q_OBJECT
public:
    myBtnOpen(QWidget *parent);
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
private:
    bool t = false;
    QPixmap pic;
};

#endif // MYBTNOPEN_H
