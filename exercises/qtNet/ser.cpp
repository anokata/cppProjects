#include "ser.h"

Server::Server(QWidget *parent) : QDialog(parent)
{
    qDebug() << "server constructor";
    tcpServer = new QTcpServer();
    if (tcpServer->listen(QHostAddress::Any, 10000))
        qDebug() << "ok listen. port 10000";
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConn));
}

Server::~Server()
{
    tcpServer->close();
    delete tcpServer;
}

void Server::newConn()
{
    qDebug() << "new connection";
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
    sendToClient(clientSocket, "Connected");
    qDebug() << "client connn";
}
        
void Server::readClient()
{

    qDebug() << "read client ";
}

void Server::sendToClient(QTcpSocket *sock, const QString &str)
{
    QByteArray a;
    QDataStream out(&a, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(a.size() - sizeof(quint16));
    sock->write(a);
    qDebug() << "send to client";
}
