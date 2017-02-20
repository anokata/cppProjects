#pragma once
#include <QtWidgets>
#include <QDebug>
#include "client.h"

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = Q_NULLPTR);
    ~ClientWidget();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void haveData();

private:
    Client *client;
};
