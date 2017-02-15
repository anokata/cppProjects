#include "qonecellwidget.h"

QOneCellWidget::QOneCellWidget(QWidget *parent) : QTableWidget(1, 1, parent)
{
    connect(this, SIGNAL (cellPressed(int, int)), this, SLOT (cellStart(int, int)));
    //connect(this, SIGNAL (itemPassed(Item*)), recipient, SLOT (passItem(Item*)));
    configure();
}

void QOneCellWidget::configure() {
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalHeader()->setResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(100);
    horizontalHeader()->setDefaultSectionSize(100);
    setDragEnabled(true);
    setDragDropOverwriteMode(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDefaultDropAction(Qt::CopyAction);
    setDropIndicatorShown(true);
    viewport()->setAcceptDrops(true);
}

QOneCellWidget::QOneCellWidget(int rows, int columns, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{
    configure();
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
    }
}

