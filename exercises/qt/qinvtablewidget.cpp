#include "qinvtablewidget.h"

void QInvTableWidget::cellStart(int row, int col) {
    dragged_item = inventory->getItem(col, row);
    qDebug()<<"TABLE cellStart" << row << col << "COUTN" << (dragged_item!=NULL?dragged_item->count:0);
    qDebug() << dragged_item;
    drag_x = col;
    drag_y = row;
}

void QInvTableWidget::cellEnter(int row, int col) {}

QInvTableWidget::QInvTableWidget(int rows, int columns, QWidget *parent, QWidget *recipient)
    : QOneCellWidget(rows, columns, parent)
{
    qDebug() << "QINV const";
    connect(this, SIGNAL (cellPressed(int, int)), this, SLOT (cellStart(int, int)));
    connect(this, SIGNAL (cellActivated(int, int)), this, SLOT (cellEnter(int, int)));
    connect(recipient, SIGNAL (itemPassed(Item*)), this, SLOT (passItem(Item*)));

    inventory = new Inventory(columns, rows);
    dragged_item = NULL;

    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem;
            this->setItem(i, j, item);
        }
    }
    //Item *i = new Item("./apple.jpg", Item::FOOD);
    //inventory->appendItem(i, 2, 2);
    refreshCells();
}
QInvTableWidget::~QInvTableWidget() {
        delete inventory;
}

void QInvTableWidget::passItem(Item * item) {
        qDebug() << "get Item SIGNAL";
        dragged_item = item;
        drag_x = -1;
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

void QInvTableWidget::dropEvent(QDropEvent *event)
{
    qDebug()<<"TABLE dropEvent";
    qDebug() << QString(event->mimeData()->text());
    QTableWidget::dropEvent(event);
    for (int i = 0; i < inventory->getRows(); ++i) {
        for (int j = 0; j < inventory->getColumns(); ++j) {
            Item * item = inventory->getItem(i, j);
            if (item != NULL) {
                //qDebug() << item->toString() << ' ';
                //qDebug() << i << ':' << j << (item) << item->count;
            }
        }
    }
    qDebug() << '\n';
    refreshCells();
}

void QInvTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QTableWidget::dragMoveEvent(event);
}

void QInvTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"TABLE dragEnterEvent";
    event->acceptProposedAction();
    QTableWidget::dragEnterEvent(event);
}

void QInvTableWidget::wipeInventory() {
    inventory->deleteItems();
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
    if(data->hasText()) //not work?
    {
        QTableWidgetItem *item = this->item(row, column);
        if(item != 0) {
            qDebug()<<"TABLE mime" << row << ' ' << column << data->text();
            Item *olditem = new Item(data->text());
            inventory->appendItem(olditem, 2, 2);
            //olditem = inventory->addItem(olditem, column, row);
        }
    }
    else
    {
        if (dragged_item != NULL) {
            QTableWidgetItem *item = this->item(row, column);
            Item *olditem = inventory->getItem(column, row);
            qDebug() << "no text" << column << row << dragged_item << olditem;
            if (olditem == NULL) {
                inventory->appendItem(dragged_item, column, row);
            } else 
            if ((item != 0) && (olditem != dragged_item)) {
                olditem = inventory->addItem(dragged_item, column, row);
                if (drag_x != -1) {
                    inventory->delItem(drag_x, drag_y);
                }
            }
        }
    }
    return QTableWidget::dropMimeData(row, column, data, action);
}

//void QInvTableWidget::mousePressEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton
//        && this->geometry().contains(event->pos())) {

//        QDrag *drag = new QDrag(this);
//        QMimeData *mimeData = new QMimeData;

//        // need know where start?
//        //Item item("./apple.jpg", Item::FOOD);
//        //mimeData->setText(item.toString());

//        drag->setMimeData(mimeData);
//        //drag->setPixmap(*imageLabel->pixmap());

//        drag->exec();
//    }
//}
