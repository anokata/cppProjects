#include "qinvtablewidget.h"

QInvTableWidget::QInvTableWidget(int rows, int columns, QWidget *parent, QWidget *recipient)
    : QOneCellWidget(rows, columns, parent)
{
    connect(this, SIGNAL (cellPressed(int, int)), this, SLOT (cellStart(int, int)));
    connect(recipient, SIGNAL (itemPassed(QString, ItemType)), this, SLOT (passItem(QString, ItemType)));

    inventory = new Inventory(columns, rows);
    draggedItem = NULL;

    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            this->setItem(i, j, item);
        }
    }
    refreshCells();
}

QInvTableWidget::~QInvTableWidget() {
        delete inventory;
}

void QInvTableWidget::refreshCells() {
    inventory->fromDB();
    for (int i = 0; i < inventory->getColumns(); ++i) {
        for (int j = 0; j < inventory->getRows(); ++j) {
            QTableWidgetItem *item = this->item(i, j);
            Item *invItem = inventory->getItem(j, i);
            item->setText("");
            item->setData(Qt::DecorationRole, QVariant());
            if (invItem != NULL) {
                item->setText(QString::number(invItem->getCount()));
                QImage image = loadFile(invItem->getImagePath());
                item->setData(Qt::DecorationRole, QPixmap::fromImage(image));
            }
        }
    }
}

void QInvTableWidget::cellStart(int row, int col) {
    draggedItem = inventory->getItem(col, row);
}

void QInvTableWidget::passItem(QString path, ItemType type) {
        draggedItem = new Item(-1, path, type);
}

void QInvTableWidget::dropEvent(QDropEvent *event)
{
    QTableWidget::dropEvent(event);
    //debug_print_all_items();
    refreshCells();
}

void QInvTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QTableWidget::dragMoveEvent(event);
}

void QInvTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
    QTableWidget::dragEnterEvent(event);
}

void QInvTableWidget::wipeInventory() {
    inventory->wipeDB();
    refreshCells();
}

bool QInvTableWidget::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{
    if (row < inventory->getRows() && column < inventory->getColumns()) {
        if (draggedItem != NULL) {
            inventory->moveItem(draggedItem, column, row);
        }
        return QTableWidget::dropMimeData(row, column, data, action);
    }
    return false;
}

void QInvTableWidget::mousePressEvent(QMouseEvent *event)
{
    QTableWidget::mousePressEvent(event);
    if (event->button() == Qt::RightButton) {
        if (inventory->eatItem(this->currentColumn(), this->currentRow())) {
            QSound::play(appleWav);
            draggedItem = NULL;
            refreshCells();
        }
    }
}

void QInvTableWidget::debugPrintAllItems() {
    for (int i = 0; i < inventory->getRows(); ++i) {
        for (int j = 0; j < inventory->getColumns(); ++j) {
            Item * item = inventory->getItem(i, j);
            if (item != NULL) {
                qDebug() << i << ':' << j << (item) << item->getCount();
            }
        }
    }
    qDebug() << '\n';
}
