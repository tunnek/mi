#ifndef MYCLICENT_H
#define MYCLICENT_H

#include <QObject>

class myClicent : public QObject
{
    Q_OBJECT
public:
    explicit myClicent(QObject *parent = nullptr);

signals:

};

#endif // MYCLICENT_H
