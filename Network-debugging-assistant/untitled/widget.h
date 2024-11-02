#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPalette>
#include <QTcpServer>
#include <QComboBox>
#include <QTimer>
#include <QUdpSocket>
#include "mylabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:

private slots:
    void on_btn_open_clicked(bool checked);

    void on_checkBox_5_clicked(bool checked);

    void label_saveData_clicked();

    void on_checkBox_4_clicked(bool checked);

    void on_pushButton_send_clicked();

    void on_newConnection();

    void on_CurrentIndexChanged();

    void setButtonIconAndSize(const QString &iconPath);

    void getLocalhostIpAddress();

    void on_checkBox_10_clicked(bool checked);

    void on_btn_broadcast_clicked();

    void on_newReadData();

private:
    Ui::Widget *ui;
    int sendCnt = 0;                                 //总的发送字节数
    int revCnt = 0;                                  //总的接受字节数
    QTcpServer *server;                              //服务端
    QTcpSocket *clientSocket = nullptr;              //用于服务端连接客户端
    QTcpSocket *socket;                              //客户端
    int currentIndex;                                //当前索引
    QTimer* timer;                                   //定时器，用于定时发送
    QComboBox* box;
    QLineEdit* edt;
    int t = 0;                                       //记录当前索引
    QUdpSocket *con;                                 //用于UDP
    const QString ICON_PATH_MM = ":/pictures/mm.png"; // 图标路径常量
    const QString ICON_PATH_PP = ":/pictures/pp.png"; // 图标路径常量
    QString clientData;
};
#endif // WIDGET_H
