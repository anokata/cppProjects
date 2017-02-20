#pragma once
#include <QtNetwork>
#include <QtWidgets>
#include <QDebug>
#include <QVector>

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = Q_NULLPTR);
    ~ServerWidget();

private slots:
    void newConn();
    void readClient();

private:
    void sendToClient(QTcpSocket *sock, const QString &str);
    QTcpServer *tcpServer;
    void mousePressEvent(QMouseEvent *event);
    quint16 blockSize;
    QString data;
    QVector<QTcpSocket*> clients;
};
