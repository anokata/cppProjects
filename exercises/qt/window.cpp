#include "window.h"
#include <QPushButton>
#include <QFont>
#include <QApplication>

Window::Window(QWidget *parent) : QWidget(parent)
{
    setFixedSize(100, 50);

    QFont font("DejaVu Sans Mono");
    //exit_button->setFont(font);
    exit_button = new QPushButton(QString("Выход"), this);
    exit_button->setGeometry(10, 10, 80, 30);
    exit_button->setLayoutDirection(Qt::RightToLeft);
    connect(exit_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
}

