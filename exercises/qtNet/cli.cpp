#include "cli.h"

ClientWidget::ClientWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "(client)construct(cli)";
    sock = new QTcpSocket(this);
    sock->connectToHost("127.0.0.1", 10000);
    connect(sock, SIGNAL(connected()), this, SLOT(connected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

ClientWidget::~ClientWidget()
{
    delete sock;
}

void ClientWidget::mousePressEvent(QMouseEvent *event)
{
    sendToServer();
}

void ClientWidget::readyRead()
{
    qDebug() << "(client)ready read";
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

void ClientWidget::connected()
{

    qDebug() << "(client)connected(client)";
}
void ClientWidget::error(QAbstractSocket::SocketError)
{

    qDebug() << "(client)error";
}
void ClientWidget::sendToServer()
{
    QByteArray a;
    QDataStream out(&a, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << QTime::currentTime() << QString("Message from client");
    out.device()->seek(0);
    out << quint16(a.size() - sizeof(quint16));
    sock->write(a);
    qDebug() << "(client)send";
}
