#pragma once
#include <QtNetwork>
#include <QtWidgets>
#include <QDebug>

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = Q_NULLPTR);
    ~ClientWidget();
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
