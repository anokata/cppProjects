#pragma once
#include <QtNetwork>
#include <QtWidgets>
#include <QDebug>

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = Q_NULLPTR);
    ~Client();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void readyRead();
    void sendToServer();
    void connected();
    void error(QAbstractSocket::SocketError);

private:
    QTcpSocket *sock;
    quint16 blockSize;
    QString data;
};
