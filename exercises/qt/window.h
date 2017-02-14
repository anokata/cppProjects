#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QHeaderView>
#include <QImage>
#include <QLabel>
#include "qinvtablewidget.h"
#include "item.h"
#include "inventory.h"

class QPushButton;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QPushButton *exit_button;
    QInvTableWidget *inventoryWidget;
    QImage image;
    QLabel *imageLabel;
    Inventory *inventory;

signals:

public slots:

private:

};

#endif // WINDOW_H
