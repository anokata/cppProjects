#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    exitButton = new QPushButton(trUtf8("Выход"), this);
    newgameButton = new QPushButton(trUtf8("Начать"), this);
    exitButton->setLayoutDirection(Qt::RightToLeft);

    this->setGeometry(0, 0, parent->width(), 40);
    newgameButton->setGeometry(10, 10, 100, 30);
    exitButton->setGeometry(parent->width() - 90, 10, 80, 30);

    connect(exitButton, SIGNAL (clicked()), parent, SLOT (exit()));
    connect(newgameButton, SIGNAL (clicked()), parent, SLOT (newgame()));
}

MainMenu::~MainMenu()
{
    delete exitButton;
    delete newgameButton;
}

void MainMenu::disable()
{
    newgameButton->setEnabled(false);
    exitButton->setEnabled(false);
}

void MainMenu::enable()
{
    newgameButton->setEnabled(true);
    exitButton->setEnabled(true);
}
