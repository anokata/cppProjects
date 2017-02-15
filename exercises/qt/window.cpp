#include "window.h"
#include <QPushButton>
#include <QApplication>
#include <QDir>
#include <QMouseEvent>
#include <QDebug>

// TODO: 
//виджет "Главное меню" contain buttons.
// виджет "Игровое поле" contain table, item (source)
// размер инвентаря.
// главное меню. скрыть кнопки начала и выход. блок одной ячейки
// выделить модуль БД
// запретить драг правой
// comments to methods. ui create
// private методы убрать, задать интерфейс.
// сделать чтобы одноячейковый не принимал и не перерисовался?
//
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

    exit_button = new QPushButton(trUtf8("Выход"), this);
    exit_button->setGeometry(WINDOW_WIDTH - 90, 10, 80, 30);
    exit_button->setLayoutDirection(Qt::RightToLeft);
    connect(exit_button, SIGNAL (clicked()), this, SLOT (exit()));
    newgame_button = new QPushButton(trUtf8("Начать"), this);
    newgame_button->setGeometry(10, 10, 100, 30);
    connect(newgame_button, SIGNAL (clicked()), this, SLOT (newgame()));
    mainMenu = new QPushButton(trUtf8("Главное меню"), this);
    mainMenu->setGeometry(450, 510, 120, 30);
    mainMenu->setLayoutDirection(Qt::RightToLeft);
    connect(mainMenu, SIGNAL (clicked()), this, SLOT (goMainMenu()));
    mainMenu->setEnabled(false);

    setAcceptDrops(true);
}

void Window::goMainMenu() {
    inventoryWidget->setEnabled(false);
    oneItem->setEnabled(false);
    mainMenu->setEnabled(false);
    newgame_button->setEnabled(true);
    exit_button->setEnabled(true);
}

void Window::newgame() {
    inventoryWidget->setEnabled(true);
    oneItem->setEnabled(true);
    mainMenu->setEnabled(true);
    newgame_button->setEnabled(false);
    exit_button->setEnabled(false);
    inventoryWidget->wipeInventory();
}

void Window::exit() {
    QApplication::instance()->quit();
    inventoryWidget->wipeInventory();
}

Window::~Window() {
    delete inventoryWidget;
    delete exit_button;
    delete oneItem;
}

void Window::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
    }
}

void Window::dragEnterEvent(QDragEnterEvent *event)
{
    if (inventoryWidget->geometry().contains(event->pos())) {
        event->acceptProposedAction();
    }
}

void Window::dropEvent(QDropEvent *event)
{
    if (inventoryWidget->geometry().contains(event->pos())) {
        inventoryWidget->dropEvent(event);
    }
}

