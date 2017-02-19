#include "ser.h"

Server::Server(QWidget *parent) : QWidget(parent)
{
    qDebug() << "(server)constructor";
    tcpServer = new QTcpServer();
    if (tcpServer->listen(QHostAddress::Any, 10000))
        qDebug() << "ok listen. port 10000";
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConn()));
}

Server::~Server()
{
    tcpServer->close();
    delete tcpServer;
}

void Server::mousePressEvent(QMouseEvent *event)
{
    for (auto c : clients) {
        sendToClient(c, "Some DAta from server");
    }
}

void Server::newConn()
{
    qDebug() << "(server)new connection";
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
    sendToClient(clientSocket, "Connected");
    qDebug() << "(server)client connn";
    clients.append(clientSocket);
}
        
void Server::readClient()
{
    qDebug() << "(server)read from client ";
    QTcpSocket* sock = (QTcpSocket*)sender();
    QDataStream in(sock);
    data = "";
    in.setVersion(QDataStream::Qt_5_5);
    for (;;) {
        if (!blockSize) {
            if (sock->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> blockSize;
        }

        if (sock->bytesAvailable() < blockSize) {
            break;
        }

        QTime time;
        QString str;
        in >> time >> str;
        data += time.toString() + " " + str + '\n';
        blockSize = 0;
    }
    qDebug() << data;
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
    qDebug() << "(server)send to client";
}
