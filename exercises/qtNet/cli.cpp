#include "cli.h"

ClientWidget::ClientWidget(QWidget *parent) : QWidget(parent)
{
    client = new Client("127.0.0.1", 10000);
    connect(client, SIGNAL(dataRecived()), this, SLOT(haveData()));
    setStyleSheet("background-color:white;");
}

void ClientWidget::haveData()
{
    qDebug() << client->getData();
}

ClientWidget::~ClientWidget()
{
    delete client;
}

void ClientWidget::mousePressEvent(QMouseEvent *event)
{
    client->sendToServer(QString("<client data>"));
}

