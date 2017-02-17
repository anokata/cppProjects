#include <QApplication>
#include <QtCore>
#include <QMessageBox>
#include <QDebug>

#include "ser.h"
#include "cli.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(Server::tr("Server/Client"));
    Server *server;
    Client *client;

    QMessageBox msgBox;
    msgBox.setText("Server?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Yes:
            server = new Server();
            server->show();
            break;
        case QMessageBox::No:
            client = new Client();
            client->show();
            break;
    }

    app.exec();
    return 0;
}
