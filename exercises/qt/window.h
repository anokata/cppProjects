#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include "qinvtablewidget.h"
#include "qonecellwidget.h"
#include "mainmenu.h"

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
    MainMenu *mainMenuWidget;
    QPushButton *mainMenu;
    QInvTableWidget *inventoryWidget;
    QOneCellWidget * oneItem;

};

#endif // WINDOW_H
