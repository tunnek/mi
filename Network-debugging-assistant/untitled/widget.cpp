#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QHostInfo>
#include <QTcpSocket>
#include <QTimer>
#include <QString>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //(1)设置组件随窗口大小变化而改变
    // 组件随着窗口大小变化而改变
    this->setLayout(ui->gridLayout_all);
    // 设置底部 widget 随窗口变化自动调整布局
    ui->widgetBottom->setLayout(ui->horizontalLayout_6);


    //(2)打开/关闭按键的初始化
    // 设置打开/关闭按键为可检查状态
    ui->btn_open->setCheckable(true);
    // 设置打开/关闭按键为透明背景
    ui->btn_open->setStyleSheet("QPushButton {"
                                "background-color: transparent;"
                                "}");

    // 设置打开/关闭按键的图标和大小
    setButtonIconAndSize(ICON_PATH_MM);

    //(3)设置QLabel和QFrame组件的样式
    //设置QLabel组件为透明
    ui->label_sendCnt->setStyleSheet("QLabel {background-color: transparent;}");
    ui->label_revCnt->setStyleSheet("QLabel {background-color: transparent;}");
    //设置QFrame组件的样式
    for(int i = 2; i <= 3; i++){
        QString frame = QString("frame_%1").arg(i);
        QFrame* fra = findChild<QFrame *>(frame);
        if(fra){
            fra->setFrameShape(QFrame::Box);             //设置边框形状
            fra->setFrameShadow(QFrame::Raised);         //设置边框阴影
        }
    }

    //(4)信号与槽函数的绑定
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){                                          //1.定时器超时槽函数，用于实现循环发送
        on_pushButton_send_clicked();
    });
    connect(ui->pushButton_resetCount, &QPushButton::clicked, this, [=](){                 //2.复位按键槽函数
        revCnt = 0;
        sendCnt = 0;
        ui->label_sendCnt->setText("发送：0");
        ui->label_revCnt->setText("接受：0");
    });
    connect(ui->label_saveData, &myLabel::clicked, this, &Widget::label_saveData_clicked); //3.保存数据槽函数
    connect(ui->label_clearData, &myLabel::clicked, this, [=](){                           //4.清除接受槽函数
        ui->textEdit->clear();
    });
                                                                                           //5.索引发送改变时槽函数
    connect(ui->comboBox_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Widget:: on_CurrentIndexChanged);

    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Widget::on_newConnection);          //6.服务端有新连接时槽函数



    //(5)获取本地主机Ip地址并更新组件
    getLocalhostIpAddress();

    //(6)添加新的组件到垂直布局中
    // 创建并设置新的 QLineEdit
    edt = new QLineEdit(this);
    edt->setText("8080");

    // 将组件添加到垂直布局中
    ui->verticalLayout->addWidget(edt);
    edt->show();
    ui->lineEdit_rev->setText("192.168.238.1");
    ui->lineEdit_revHonts->setText("8080");

}

Widget::~Widget()
{
    delete ui;
}

//打开按键槽函数
void Widget::on_btn_open_clicked(bool checked)
{
    if (checked) {
        QString localIpAddress = ui->comboBox_2->currentText();  // 获取用户输入的本地主机ip地址
        QHostAddress ipaddress = QHostAddress(localIpAddress);
        if (ui->comboBox_1->currentIndex() == 2) {                // 当前用户所选的是服务端==============================
            QString honts = edt->text();                              // 获取用户输入的端口号
            quint16 port = honts.toUInt();
            server->listen(ipaddress, port);                          // 根据ip地址和端口号开始监听
            ui->btn_open->setIcon(QIcon(":/pictures/pp.png"));        // 设置按键的图片
            ui->comboBox_1->setEnabled(false);
            t = 2;
        } else if (ui->comboBox_1->currentIndex() == 1) {           // 当前用户所选的是客户端=============================
            QHostAddress remIpaddress;
            quint16 remPort;
            QString data = box->currentText();                        // 获取用户输入的远程主机ip地址与端口号
            QStringList parts = data.split(":");                      // 使用 ':' 字符分割字符串
            if (parts.size() == 2) {
                QString ipAddress = parts[0];
                QString port = parts[1];
                remIpaddress = QHostAddress(ipAddress);               // 远程主机ip地址
                remPort = port.toUInt();                              // 远程主机端口号
            } else {
                qDebug() << "Invalid address format!";
                return; // 提前返回，避免继续执行
            }
            socket = new QTcpSocket(this);
            connect(socket, &QTcpSocket::connected, this, [=]() {                                  //7.客户端连接到服务端槽函数
                ui->btn_open->setIcon(QIcon(":/pictures/pp.png"));
                ui->comboBox_1->setEnabled(false);
            });

            connect(socket, &QTcpSocket::readyRead, this, [=]() {                                  //8.客户端接收到数据槽函数
                int sum = 0;
                QByteArray data = socket->readAll(); // 读取接收到的数据
                sum = data.size();
                revCnt += sum;
                ui->label_revCnt->setText("接受: "+ QString::number(revCnt));
                // Hex显示是否勾选
                if (ui->checkBox_4->isChecked()) {
                    data = data.toHex().toUpper();
                }
                //换行是否勾选
                if (ui->checkBox_2->isChecked()){
                    data.append("\r\n");
                }

                //添加时间是否勾选
                if(ui->checkBox_3->isChecked()){
                    QDate currentDate = QDate::currentDate();
                    QTime currentTime = QTime::currentTime();
                    int year = currentDate.year();
                    int hour = currentTime.hour();
                    int minute = currentTime.minute();
                    int second = currentTime.second();
                    QString timeString = QString("【%1 %2:%3:%4】").arg(year)
                                                                  .arg(hour,2,10,QChar('0'))
                                                                  .arg(minute,2,10,QChar('0'))
                                                                  .arg(second,2,10,QChar('0'));
                    ui->textEdit->append(timeString);
                }
                ui->textEdit->insertPlainText(QString::fromLocal8Bit(data));
            });

            connect(socket, &QTcpSocket::disconnected, this, [=]() {                                 //9.客户端与服务端断开连接槽函数
                qDebug() << "Disconnected from server.";
                socket->deleteLater(); // 断开连接时删除 socket
            });

            socket->connectToHost(remIpaddress, remPort);            // 尝试连接服务端
            t = 1;
        } else {                                                   // 当前用户所选的是UDP==================================
            con = new QUdpSocket(this);
            QString honts = edt->text();
            qDebug() << "localIpAddress: " << localIpAddress;
            qDebug() << "honts: " << honts;
            t = 0;
            if (con->bind(ipaddress, honts.toInt())) {
                ui->btn_open->setIcon(QIcon(":/pictures/pp.png"));        // 设置按键的图片
                connect(con, &QUdpSocket::readyRead, this, &Widget::on_newReadData);
                ui->label_state->setText("打开成功");
            } else {
                ui->label_state->setText("udp被占用");
                delete con; // 确保在绑定失败时释放资源
                con = nullptr;
            }
        }
    } else {
        ui->btn_open->setIcon(QIcon(":/pictures/mm.png"));       // 设置按钮图标
        ui->comboBox_1->setEnabled(true);                        // 启用下拉框

        if (t == 1) {                                            // 客户端释放资源==========================
            if(socket->state() == QAbstractSocket::ConnectedState){
                socket->disconnectFromHost();                        // a.断开与服务器的连接
                socket->deleteLater();                               // b.删除socket套接字
            }
        } else if (t == 2) {                                     // 服务端释放资源==========================
            if (server->isListening()) {
                server->close();                                     // a.关闭服务器
                qDebug() << "Server stopped listening.";
            }
        } else if (t == 0) {                                     // UDP通信资源的释放============================
            if (con) {
                con->disconnect();                                   // a.断开信号槽连接
                con->close();                                        // b.关闭网络套接字
                con->deleteLater();                                  // c.删除 UDP 套接字
            }
        }
    }
}


//保存数据槽函数
void Widget::label_saveData_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存文件"), //1.打开文件对话框，选择保存的路径和文件名
                       "C:/Users/mi/Desktop/Qt Project/Network-debugging-assistant/Data",
                       tr("Text files (*.txt *doc)"));
    qDebug() << fileName << endl;                                        //2.输出用户选择的文件名到控制台
    QFile file;
    file.setFileName(fileName);                                          //3.设置要保存的文件名（路径）
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){               //4.以“只写”模式和“文本”类型打开文件
        qDebug() << "file open error";
    }
    QTextStream out(&file);                                              //5.将 QTextEdit 的内容写入文件
    out.setCodec("UTF-8");

    out << ui->textEdit->toPlainText();
    file.close();                                                        //6.关闭文件
}

//暂停接受显示槽函数
void Widget::on_checkBox_5_clicked(bool checked)
{
    if(checked){
        ui->textEdit->setEnabled(false);
    }else{
        ui->textEdit->setEnabled(true);
    }
}

//Hex显示槽函数
void Widget::on_checkBox_4_clicked(bool checked)
{
    if (checked) { // 当勾选 Hex 显示时
        QString data = ui->textEdit->toPlainText(); // 获取当前文本
        QByteArray arrayData = data.toLocal8Bit();

        // 将数据转成 Hex 格式
        QByteArray hexData = arrayData.toHex().toUpper();

        // 格式化以便每两个字符之间加一个空格
        QString lastShow;
        for (int i = 0; i < hexData.size(); i += 2) {
            lastShow += hexData.mid(i, 2) + " ";
        }

        // 清空 textEdit 并显示 Hex 数据
        ui->textEdit->clear(); // 清空文本框
        ui->textEdit->append(lastShow); // 追加 Hex 数据
    } else { // 当取消勾选 Hex 显示时
        QString hexData = ui->textEdit->toPlainText(); // 获取当前 Hex 数据
        QByteArray arrayData = QByteArray::fromHex(hexData.toLocal8Bit()); // 转换为普通文本
        QString lastShow = QString::fromLocal8Bit(arrayData); // 还原后的数据

        // 清空 textEdit 并显示还原后的数据
        ui->textEdit->clear(); // 清空文本框
        ui->textEdit->append(lastShow); // 追加还原后的普通数据
    }
}


//发送按键槽函数
void Widget::on_pushButton_send_clicked()
{
    QString data = ui->textEdit_sendData->toPlainText();                   //(1)先获取用户输入的要发送的内容
    QByteArray arrayData = data.toLocal8Bit();
    int cnt = 0;
    if (ui->checkBox_9->isChecked()) {                                     //(2)判断Hex发送是否勾选，此处为勾选
        if (0 != arrayData.size() % 2) {                                        // a.检查字节数是否是偶数
            ui->label_state->setText("input error!");
            return;
        }
        for (char c : arrayData) {                                              // b.检查是否符合Hex表达
            if (!isxdigit(c)) {
                ui->label_state->setText("input error!");
                return;
            }
        }
        arrayData = QByteArray::fromHex(arrayData);                             // c.转化为16进制
    }
                                                                           //(3).开始发送数据
    if (t == 1) {                                                               // a.客户端发送数据
        if(socket->state() == QAbstractSocket::ConnectedState){
            cnt = socket->write(arrayData);
        }else{
            ui->label_state->setText("send error!");
        }

    } else if (t == 2) {                                                        // b.服务端发送数据
        if(clientSocket->state() == QAbstractSocket::ConnectedState){
            cnt = clientSocket->write(arrayData);
        }else{
            qDebug() << clientSocket;
            ui->label_state->setText("send error!");
        }
    }else{                                                                      // c.UDP发送数据
        if(ui->lineEdit_rev->text().isEmpty() || ui->lineEdit_revHonts->text().isEmpty()){
            ui->label_state->setText("send error: address or port is empty!");
        } else {
            bool sent = con->writeDatagram(arrayData, QHostAddress(ui->lineEdit_rev->text()), ui->lineEdit_revHonts->text().toInt());
            if (!sent) {
                ui->label_state->setText("send error: failed to send datagram!");
                // 这里可以添加更多调试信息，例如打印错误信息
                qDebug() << "Error sending datagram to" << ui->lineEdit_rev->text() << "on port" << ui->lineEdit_revHonts->text();
            } else {
                ui->label_state->setText("send success!");
            }
        }


    }

    if (cnt == -1) {                                                       //(4)判断是否发送成功
        ui->label_state->setText("send error!");
    } else {
        if (ui->checkBox_8->isChecked()) {
            ui->textEdit_sendData->clear();
        }
        sendCnt += cnt;
        ui->label_state->setText("send OK!");
        ui->label_sendCnt->setText("发送: " + QString::number(sendCnt));
    }
}

//服务端接受到新的连接时的槽函数
void Widget::on_newConnection()
{
    // 获取新连接
    clientSocket = server->nextPendingConnection();

    if (clientSocket) {
        QHostAddress clientAddress = clientSocket->peerAddress();
        quint16 clientPort = clientSocket->peerPort();
        clientData = QString("[Receive from %1:%2]").arg(clientAddress.toString()).arg(clientPort);
        // 当客户端发送来消息时，将消息显示到控件中
        connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
            // 读取客户端发送过来的消息
            QByteArray data = clientSocket->readAll();

            // 统计消息的字数并将总接受字数刷新到控件中
            int cnt = data.size();
            revCnt += cnt;
            ui->label_revCnt->setText("接受: " + QString::number(revCnt));

            // Hex显示是否勾选
            if (ui->checkBox_4->isChecked()) {
                data = data.toHex().toUpper();
            }
            //换行是否勾选
            if (ui->checkBox_2->isChecked()){
                data.append("\r\n");
            }

            if(clientData.size() > 0){
                ui->textEdit->append(clientData);
                clientData.clear();
            }

            //添加时间是否勾选
            if(ui->checkBox_3->isChecked()){
                QDate currentDate = QDate::currentDate();
                QTime currentTime = QTime::currentTime();
                int year = currentDate.year();
                int hour = currentTime.hour();
                int minute = currentTime.minute();
                int second = currentTime.second();
                QString timeString = QString("【%1 %2:%3:%4】").arg(year)
                                                              .arg(hour,2,10,QChar('0'))
                                                              .arg(minute,2,10,QChar('0'))
                                                              .arg(second,2,10,QChar('0'));
                ui->textEdit->append(timeString);
            }
            ui->textEdit->insertPlainText(QString::fromLocal8Bit(data));
        });

        // 当客户端断开连接时释放
        connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
            qDebug() << "Client disconnected:" << clientAddress << ":" << clientPort;
            clientSocket->deleteLater(); // 释放资源
        });
    } else {
        qDebug() << "Failed to accept new connection.";
    }
}


// 当QComboBox组件的索引发生改变时的槽函数
void Widget::on_CurrentIndexChanged()
{
    // 获取用户当前选择的索引
    currentIndex = ui->comboBox_1->currentIndex();

    // 删除垂直布局中的第六个组件（如果存在）
    if (ui->verticalLayout->count() >= 6) {
        QWidget* widget = ui->verticalLayout->itemAt(5)->widget(); //获取第六个控件
        if (widget) {
            ui->verticalLayout->removeWidget(widget);              //从布局中移除
            widget->deleteLater();                                 //删除组件
        }
    }

    if (currentIndex == 1) {                            // 用户选择了客户端=================================
        ui->label_4->setEnabled(false);
        ui->lineEdit_rev->setEnabled(false);
        ui->label_4->setEnabled(false);
        ui->lineEdit_revHonts->setEnabled(false);
        ui->btn_broadcast->setEnabled(false);

        ui->label_2->setText("(2)本地主机地址");
        ui->label_3->setText("(3)远程主机地址");
        box = new QComboBox(this);                            //创建新的 QComboBox
        box->addItem("192.168.238.1 :8080");                   //向组件中添加内容
        box->setEditable(true);                               //设置组件中的内容可修改

        ui->verticalLayout->addWidget(box);                   //将组件添加到垂直布局中
        box->show();                                          //显示新创建的 QComboBox
    }else if(currentIndex == 0){                         // 用户选择了UDP=================================
        ui->lineEdit_rev->setText("192.168.238.1");
        ui->lineEdit_revHonts->setText("8080");

        ui->label_4->setEnabled(true);
        ui->lineEdit_rev->setEnabled(true);
        ui->label_4->setEnabled(true);
        ui->lineEdit_revHonts->setEnabled(true);
        ui->btn_broadcast->setEnabled(true);

        ui->label_2->setText("(2)本地主机地址");
        ui->label_3->setText("(3)本地主机端口");
        edt = new QLineEdit(this);                            //创建新的 QLineEdit
        edt->setText("8080");                                 //设置新的QLineEdit显示的内容

        ui->verticalLayout->addWidget(edt);                   //将组件添加到垂直布局中
        edt->show();                                          //显示新创建的 QLineEdit
    }else{                                               // 用户选择了服务端=================================
        ui->label_4->setEnabled(false);
        ui->lineEdit_rev->setEnabled(false);
        ui->label_4->setEnabled(false);
        ui->lineEdit_revHonts->setEnabled(false);
        ui->btn_broadcast->setEnabled(false);

        ui->label_2->setText("(2)本地主机地址");
        ui->label_3->setText("(3)本地主机端口");
        edt = new QLineEdit(this);                            //创建新的 QLineEdit
        edt->setText("8080");                                 //设置新的QLineEdit显示的内容

        ui->verticalLayout->addWidget(edt);                   //将组件添加到垂直布局中
        edt->show();                                          //显示新创建的 QLineEdit
    }
}

//设置打开/关闭按键的图片
void Widget::setButtonIconAndSize(const QString &iconPath)
{
    QSize buttonSize = ui->btn_open->size();                      //获取按钮的当前大小
    ui->btn_open->setIconSize(buttonSize);                        //设置图片大小为按键的大小
    ui->btn_open->setIcon(QIcon(iconPath));                       //设置按键的图片
}

//获取本地主机ip地址并显示到组件中槽函数
void Widget::getLocalhostIpAddress()
{
    QString localHostName = QHostInfo::localHostName();          //获取本地主机名称
    QHostInfo info = QHostInfo::fromName(localHostName);         //根据本地主机名称获取本地主机信息
    QList<QHostAddress> addresses = info.addresses();            //将本地主机的所有ip地址赋值给容器中

    // 清空 comboBox_2 并添加 IPv4 地址
    ui->comboBox_2->clear();
    for (const auto& address : addresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            qDebug() << "IPv4 Address:" << address.toString();
            ui->comboBox_2->addItem(address.toString());
        }
    }
}

//定时发送槽函数
void Widget::on_checkBox_10_clicked(bool checked)
{
    if(checked){
        timer->setInterval(ui->lineEdit_msData->text().toInt()); //设置定时器定时时间
        timer->start();                                          //启动定时器
    }else{
        timer->stop();                                           //停止定时器
    }
}

//广播按键槽函数
void Widget::on_btn_broadcast_clicked()
{
    QString message = ui->textEdit_sendData->toPlainText();                      // 获取要广播的消息
    QByteArray arrayData = message.toLocal8Bit();                                // 转换为 QByteArray
    QString honts = ui->lineEdit_revHonts->text();
    if(honts == NULL){
        ui->label_state->setText("send error!");
        return;
    }
    quint16 port = honts.toUInt();                                               // 获取用户输入的端口号

    QHostAddress broadcastAddress = QHostAddress::Broadcast;                     // 设置广播地址
    qint64 bytesWritten = con->writeDatagram(arrayData, broadcastAddress, port); // 发送广播
    if (bytesWritten == -1) {
        ui->label_state->setText("Broadcast error!");                           // 处理发送错误
        qDebug() << "Broadcast error:" << con->errorString();
    } else {
        ui->label_state->setText("Broadcast sent!");                            // 成功发送广播
    }
}

//UDP连接时接受数据槽函数
void Widget::on_newReadData()
{
    // 从UDP套接字接收数据
    while (con->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(int(con->pendingDatagramSize())); // 确保接收缓冲区大小合适

        QHostAddress sender; // 发送者的地址
        quint16 senderPort;  // 发送者的端口
        con->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort); // 读取数据

        // 打印接收到的消息和发送者信息
        qDebug() << "Received datagram from" << sender.toString() << ":" << senderPort << "Data:" << buffer;

        // 更新接收计数
        int cnt = buffer.size();
        revCnt += cnt;
        ui->label_revCnt->setText("接受: " + QString::number(revCnt));

        // 判断是否以十六进制显示
        if (ui->checkBox_4->isChecked()) {
            QByteArray tmpHexString = buffer.toHex().toUpper();
            if (ui->checkBox_2->isChecked()) tmpHexString.append("\r\n");
            ui->textEdit->insertPlainText("【rev from: " + sender.toString() + "】" + tmpHexString);
        } else {
            QString nowData = QString::fromLocal8Bit(buffer);
            if (ui->checkBox_2->isChecked()) nowData.append("\r\n");
            ui->textEdit->insertPlainText("【rev from: " + sender.toString() + "】" + nowData);
        }
    }
}

