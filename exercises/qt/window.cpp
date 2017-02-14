#include "window.h"
#include <QPushButton>
#include <QFont>
#include <QApplication>

Window::Window(QWidget *parent) : QWidget(parent)
{
    setFixedSize(500, 550);
    setGeometry(0, 0, 500, 500);

    //QFont font("DejaVu Sans Mono");
    //exit_button->setFont(font);
    inventory = new Inventory(this);
    inventory->setGeometry(10, 100, 200, 200);
    exit_button = new QPushButton(tr("xit"), this);
    exit_button->setGeometry(10, 10, 80, 30);
    exit_button->setLayoutDirection(Qt::RightToLeft);
    connect(exit_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
}

