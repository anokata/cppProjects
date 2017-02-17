#include "cli.h"

Client::Client(QWidget *parent) : QDialog(parent)
{
    qDebug() << "construct(cli)";
    sock = new QTcpSocket(this);
    sock->connectToHost("localhost", 10000);
    connect(sock, SIGNAL(connected()), this, SLOT(connected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(sock, SIGNAL(error(QAbstractSocket::socketError)), this, SLOT(error(QAbstractSocket::socketError)));

    //connect(this, SIGNAL(returnPressed()), this, SLOT(sendToServer()));
}

Client::~Client()
{
    delete sock;
}

void Client::readyRead()
{

    qDebug() << "ready(cli)";
}
void Client::sendToServer()
{

    qDebug() << "send(client)";
}
void Client::connected()
{

    qDebug() << "connected(client)";
}
void Client::error(QAbstractSocket::SocketError)
{

    qDebug() << "error";
}
