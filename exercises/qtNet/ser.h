#pragma once
#include <QtWidgets>
#include <QDebug>
#include "server.h"

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = Q_NULLPTR);
    ~ServerWidget();

private slots:
    void haveData();

private:
    Server* server;
    void mousePressEvent(QMouseEvent *event);
};
