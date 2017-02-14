#include "qonecellwidget.h"

QOneCellWidget::QOneCellWidget(QWidget *parent, QWidget *recipient) : QInvTableWidget(1, 1, parent)
{
    Item * item = new Item("./apple.jpg", Item::FOOD);
    inventory->addItem(item, 0, 0);
    connect(this, SIGNAL (cellPressed(int, int)), this, SLOT (cellStart(int, int)));
    connect(this, SIGNAL (itemPassed(Item*)), recipient, SLOT (passItem(Item*)));
}

void QOneCellWidget::cellStart(int row, int col) {
    qDebug()<<"ONE cellStart" << row << col;
}

void QOneCellWidget::mousePressEvent(QMouseEvent *event) {
    QTableWidget::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        // GEN ITEM
        qDebug() << "QONE Start drag";
        Item * item = new Item("./apple.jpg", Item::FOOD);
        emit itemPassed(item);
        //emit passItem(item);
    }
}
