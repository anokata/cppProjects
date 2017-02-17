#include "cli.h"

Client::Client(QWidget *parent) : QWidget(parent)
{
    qDebug() << "(client)construct(cli)";
    sock = new QTcpSocket(this);
    sock->connectToHost("127.0.0.1", 10000);
    connect(sock, SIGNAL(connected()), this, SLOT(connected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

Client::~Client()
{
    delete sock;
}

void Client::mousePressEvent(QMouseEvent *event)
{
    sendToServer();
}

void Client::readyRead()
{
    qDebug() << "(client)ready read";
    QDataStream in(sock);
    in.setVersion(QDataStream::Qt_5_5);
    for (;;) {

    }
}
void Client::sendToServer()
{
    QByteArray a;
    QDataStream out(&a, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << QTime::currentTime() << "Message from client";
    out.device()->seek(0);
    out << quint16(a.size() - sizeof(quint16));
    sock->write(a);
    qDebug() << "(client)send";
}
void Client::connected()
{

    qDebug() << "(client)connected(client)";
}
void Client::error(QAbstractSocket::SocketError)
{

    qDebug() << "(client)error";
}
