#include "qinvtablewidget.h"

void QInvTableWidget::cellStart(int row, int col) {
    dragged_item = inventory->getItem(col, row);
    drag_x = col;
    drag_y = row;
}

void QInvTableWidget::cellEnter(int row, int col) {}

QInvTableWidget::QInvTableWidget(int rows, int columns, QWidget *parent, QWidget *recipient)
    : QOneCellWidget(rows, columns, parent)
{
    connect(this, SIGNAL (cellPressed(int, int)), this, SLOT (cellStart(int, int)));
    connect(this, SIGNAL (cellActivated(int, int)), this, SLOT (cellEnter(int, int)));
    connect(recipient, SIGNAL (itemPassed(QString, Item::Item_type)), this, SLOT (passItem(QString, Item::Item_type)));

    inventory = new Inventory(columns, rows);
    dragged_item = NULL;

    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem;
            this->setItem(i, j, item);
        }
    }
    refreshCells();
}
QInvTableWidget::~QInvTableWidget() {
        delete inventory;
}

void QInvTableWidget::passItem(QString path, Item::Item_type type) {
        dragged_item = new Item(-1, path, type);
}

QImage QInvTableWidget::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        qDebug() << "Can not load file";
        return newImage;
    }
    return newImage;
}

void QInvTableWidget::debug_print_all_items() {
    for (int i = 0; i < inventory->getRows(); ++i) {
        for (int j = 0; j < inventory->getColumns(); ++j) {
            Item * item = inventory->getItem(i, j);
            if (item != NULL) {
                qDebug() << i << ':' << j << (item) << item->count;
            }
        }
    }
    qDebug() << '\n';
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

void QInvTableWidget::refreshCells() {
    inventory->fromDB();
    for (int i = 0; i < inventory->getColumns(); ++i) {
        for (int j = 0; j < inventory->getRows(); ++j) {
            QTableWidgetItem *item = this->item(i, j);
            Item *inv_item = inventory->getItem(j, i);
            item->setText("");
            item->setData(Qt::DecorationRole, QVariant());
            if (inv_item != NULL) {
                item->setText(QString::number(inv_item->count));
                QImage image = loadFile(inv_item->getImagePath());
                item->setData(Qt::DecorationRole, QPixmap::fromImage(image));
            }
        }
    }
}

bool QInvTableWidget::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{
    if (dragged_item != NULL) {
        inventory->appendItem(dragged_item, column, row);
    }
    return QTableWidget::dropMimeData(row, column, data, action);
}

void QInvTableWidget::mousePressEvent(QMouseEvent *event)
{
    QTableWidget::mousePressEvent(event);
    if (event->button() == Qt::RightButton) {
        if (inventory->eatItem(this->currentColumn(), this->currentRow())) {
        //sound if eated
        refreshCells();
        }
    }
}
