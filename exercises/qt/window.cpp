#include "window.h"
#include <QPushButton>
#include <QFont>
#include <QApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QDir>
#include <QMouseEvent>
#include <QDebug>

// TODO: 
// БД. начало игры 
// private методы убрать, задать интерфейс.
// comments to methods. ui create
// сделать чтобы одноячейковый не принимал и не перерисовался?
// Съедать + звук
// выделить модуль БД
// Баг при перетаскивании на себя, fixed
// try Qt5
// вылет за границу
// главное меню. скрыть кнопки начала и выход. блок одной ячейки
// рисовать в углу цифру
Window::Window(QWidget *parent) : QWidget(parent)
{
    const int INV_DIMENSION = 3;
    setFixedSize(600, 650);
    setGeometry(0, 0, 600, 600);

    //QFont font("DejaVu Sans Mono");
    //exit_button->setFont(font);
    //= new Inventory(this);
    oneItem = new QOneCellWidget(this);
    oneItem->setGeometry(450, 300, 120, 120);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(Qt::DecorationRole, QPixmap::fromImage(inventoryWidget->loadFile("./apple.jpg")));
    oneItem->setItem(0, 0, item);

    inventoryWidget = new QInvTableWidget(INV_DIMENSION, INV_DIMENSION, this, oneItem);
    inventoryWidget->setGeometry(10, 100, 400, 400);

    exit_button = new QPushButton(trUtf8("Выход"), this);
    exit_button->setGeometry(10, 10, 80, 30);
    exit_button->setLayoutDirection(Qt::RightToLeft);
    connect(exit_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
    newgame_button = new QPushButton(trUtf8("Новая игра"), this);
    newgame_button->setGeometry(110, 10, 100, 30);
    connect(newgame_button, SIGNAL (clicked()), this, SLOT (newgame()));

    setAcceptDrops(true);
}

void Window::newgame() {
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

