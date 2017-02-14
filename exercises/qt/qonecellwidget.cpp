#include "qonecellwidget.h"

QOneCellWidget::QOneCellWidget(QWidget *parent) : QInvTableWidget(1, 1, parent)
{
    Item * item = new Item("./apple.jpg", Item::FOOD);
    inventory->addItem(item, 0, 0);
    connect(this, SIGNAL (cellPressed(int, int)), this, SLOT (cellStart(int, int)));
}

void QOneCellWidget::cellStart(int row, int col) {
    qDebug()<<"ONE cellStart" << row << col;
}

void QOneCellWidget::mousePressEvent(QMouseEvent *event) {
    QTableWidget::mousePressEvent(event);
    /*if (event->button() == Qt::LeftButton) {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
        // GEN ITEM
        qDebug() << "QONE Start drag";
        Item item("./apple.jpg", Item::FOOD);
        mimeData->setText(item.toString());
        drag->setMimeData(mimeData);
        //drag->setPixmap(*imageLabel->pixmap());
        drag->exec();
    }
    */
}
