#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>

class myServer : public QObject
{
    Q_OBJECT
public:
    myServer(){
        QTcpServer *server = new QTcpServer(this);
        connect(server, &QTcpServer::newConnection, this, &myServer::onnewConnection);
        server->listen(QHostAddress::Any, ); //开始监听
    }
private slots:
    void onnewConnection();
signals:

};

#endif // MYSERVER_H
