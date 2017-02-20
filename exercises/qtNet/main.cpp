#include <QApplication>
#include <QtCore>
#include <QMessageBox>
#include <QDebug>

#include "ser.h"
#include "cli.h"

void chooseClientOrServer() 
{
    ServerWidget *server;
    ClientWidget *client;
    QMessageBox msgBox;

    msgBox.setText("Run server?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Yes:
            server = new ServerWidget();
            server->show();
            break;
        case QMessageBox::No:
            client = new ClientWidget();
            client->show();
            break;
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ServerWidget::tr("Server/Client"));
    chooseClientOrServer();
    app.exec();
    return 0;
}
