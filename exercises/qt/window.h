#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include "qinvtablewidget.h"
#include "qonecellwidget.h"

class QPushButton;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    ~Window();

signals:

public slots:
    void newgame();
    void exit();
    void goMainMenu();

private:
    QPushButton *exit_button;
    QPushButton *newgame_button;
    QPushButton *mainMenu;
    QInvTableWidget *inventoryWidget;
    QOneCellWidget * oneItem;

};

#endif // WINDOW_H
