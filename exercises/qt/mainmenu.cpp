#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    exit_button = new QPushButton(trUtf8("Выход"), this);
    newgame_button = new QPushButton(trUtf8("Начать"), this);
    exit_button->setLayoutDirection(Qt::RightToLeft);

    this->setGeometry(0, 0, parent->width(), 40);
    newgame_button->setGeometry(10, 10, 100, 30);
    exit_button->setGeometry(parent->width() - 90, 10, 80, 30);

    connect(exit_button, SIGNAL (clicked()), parent, SLOT (exit()));
    connect(newgame_button, SIGNAL (clicked()), parent, SLOT (newgame()));
}

MainMenu::~MainMenu() {
    delete exit_button;
    delete newgame_button;
}

void MainMenu::disable() {
    newgame_button->setEnabled(false);
    exit_button->setEnabled(false);
}

void MainMenu::enable() {
    newgame_button->setEnabled(true);
    exit_button->setEnabled(true);
}
