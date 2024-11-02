#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel(QWidget *parent);

protected:
    void mousePressEvent(QMouseEvent *ev) override;

signals:
    void clicked();
};

#endif // MYLABEL_H
