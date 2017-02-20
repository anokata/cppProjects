#include "ser.h"

ServerWidget::ServerWidget(QWidget *parent) : QWidget(parent)
{
    server = new Server(10000);
    connect(server, SIGNAL(dataRecivedS()), this, SLOT(haveData()));
    setStyleSheet("background-color:blue;");
}

ServerWidget::~ServerWidget()
{
    delete server;
}

void ServerWidget::mousePressEvent(QMouseEvent *event)
{
    server->sendData(QString("<Data from server>"));
}

void ServerWidget::haveData()
{
    qDebug() << server->popData();
}

