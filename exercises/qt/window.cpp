#include "window.h"
#include <QPushButton>
#include <QApplication>

// TODO: 
//виджет "Главное меню" contain buttons.
// виджет "Игровое поле" contain table, item (source)
// размер инвентаря. есть?
// главное меню. скрыть кнопки начала и выход. блок одной ячейки
// выделить модуль БД
// comments to methods. ui create
// private методы убрать, задать интерфейс.
// fixed? сделать чтобы одноячейковый не принимал и не перерисовался?
// отличать right click from drag
//
// refactor - rename
// try Qt5
// переделать звук
// переставить методы от главных к второстепенным
// корректно отконнектится от бд
// можно бы хранить только уникальные предметы а в инвентаре уже описывать количество.
Window::Window(QWidget *parent) : QWidget(parent)
{
    const int INV_DIMENSION = 3;
    const int WINDOW_WIDTH = 600;
    setFixedSize(WINDOW_WIDTH, WINDOW_WIDTH);
    setGeometry(0, 0, WINDOW_WIDTH, WINDOW_WIDTH);

    oneItem = new QOneCellWidget(this);
    oneItem->setGeometry(450, 300, 120, 120);
    oneItem->setEnabled(false);

    inventoryWidget = new QInvTableWidget(INV_DIMENSION, INV_DIMENSION, this, oneItem);
    inventoryWidget->setGeometry(10, 100, 400, 400);
    inventoryWidget->setEnabled(false);

    mainMenu = new QPushButton(trUtf8("Главное меню"), this);
    mainMenu->setGeometry(450, 510, 120, 30);
    mainMenu->setLayoutDirection(Qt::RightToLeft);
    mainMenu->setEnabled(false);
    // Signals
    connect(mainMenu, SIGNAL (clicked()), this, SLOT (goMainMenu()));

    mainMenuWidget = new MainMenu(this);
}

Window::~Window() {
    delete inventoryWidget;
    delete oneItem;
    delete mainMenu;
    delete mainMenuWidget;
}

void Window::goMainMenu() {
    inventoryWidget->setEnabled(false);
    oneItem->setEnabled(false);
    mainMenu->setEnabled(false);
    mainMenuWidget->enable();
}

void Window::newgame() {
    inventoryWidget->setEnabled(true);
    oneItem->setEnabled(true);
    mainMenu->setEnabled(true);
    inventoryWidget->wipeInventory();
    mainMenuWidget->disable();
}

void Window::exit() {
    QApplication::instance()->quit();
    inventoryWidget->wipeInventory();
}

