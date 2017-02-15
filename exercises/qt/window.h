#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QHeaderView>
#include <QImage>
#include <QLabel>
#include "qinvtablewidget.h"
#include "item.h"
#include "inventory.h"
#include "qonecellwidget.h"

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
    QPushButton *newgame_button;
    QInvTableWidget *inventoryWidget;
    QOneCellWidget * oneItem;


signals:

public slots:
    void newgame();

private:

};

#endif // WINDOW_H
