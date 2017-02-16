#include "window.h"
#include <QApplication>

// TODO: 
// выделить модуль БД
// comments to methods. ui create
// корректно отконнектится от бд
// refactor - rename
// case -> _ to cK
//
// при закрытии тоже чистить базу?
// переставить методы от главных к второстепенным
// можно бы хранить только уникальные предметы а в инвентаре уже описывать количество.
Window::Window(QWidget *parent) : QWidget(parent)
{
    const int WINDOW_WIDTH = 600;
    setFixedSize(WINDOW_WIDTH, WINDOW_WIDTH);
    setGeometry(0, 0, WINDOW_WIDTH, WINDOW_WIDTH);

    mainMenuWidget = new MainMenu(this);
    gameField = new GameField(this);
}

Window::~Window() {
    delete mainMenuWidget;
    delete gameField;
}

void Window::goMainMenu() {
    gameField->disable();
    mainMenuWidget->enable();
}

void Window::newgame() {
    gameField->enable();
    mainMenuWidget->disable();
}

void Window::exit() {
    gameField->enable();
    QApplication::instance()->quit();
}

