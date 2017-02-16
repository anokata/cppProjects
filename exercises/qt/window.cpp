#include "window.h"
#include <QApplication>

Window::Window(QWidget *parent) : QWidget(parent)
{
    const int WINDOW_WIDTH = 600;
    setFixedSize(WINDOW_WIDTH, WINDOW_WIDTH);
    setGeometry(0, 0, WINDOW_WIDTH, WINDOW_WIDTH);

    mainMenuWidget = new MainMenu(this);
    gameField = new GameField(this);
}

Window::~Window()
{
    delete mainMenuWidget;
    delete gameField;
}

void Window::goMainMenu()
{
    gameField->disable();
    mainMenuWidget->enable();
}

void Window::newgame()
{
    gameField->enable();
    mainMenuWidget->disable();
}

void Window::exit()
{
    gameField->enable();
    QApplication::instance()->quit();
}

