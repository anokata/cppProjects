#pragma once
#include <QtNetwork>
#include <QtWidgets>
#include <QDebug>

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = Q_NULLPTR);
    ~Server();

private slots:
    void newConn();
    void readClient();

private:
    void sendToClient(QTcpSocket *sock, const QString &str);
    QTcpServer *tcpServer;
    void mousePressEvent(QMouseEvent *event);
};
