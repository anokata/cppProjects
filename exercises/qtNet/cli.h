#pragma once
#include <QtNetwork>
#include <QtWidgets>
#include <QDebug>

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = Q_NULLPTR);
    ~Client();

private slots:
    void readyRead();
    void sendToServer();
    void connected();
    void error(QAbstractSocket::SocketError);

private:
    QTcpSocket *sock;
};
