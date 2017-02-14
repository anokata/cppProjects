#include "qinvtablewidget.h"

QInvTableWidget::QInvTableWidget(QWidget *parent) : QTableWidget(parent)
{}

void QInvTableWidget::cellStart(int row, int col) {
    //qDebug()<<"TABLE cellStart" << row << ' ' << col;
    dragged_item = inventory->getItem(col, row);
    qDebug() << dragged_item;
    drag_x = col;
    drag_y = row;
}

void QInvTableWidget::cellEnter(int row, int col) {}

QInvTableWidget::QInvTableWidget(int rows, int columns, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{
        setDragEnabled(true);
        setDragDropOverwriteMode(true);
        setDragDropMode(QAbstractItemView::DragDrop);
        setDefaultDropAction(Qt::CopyAction);

        connect(this, SIGNAL (cellPressed(int, int)), this, SLOT (cellStart(int, int)));
        connect(this, SIGNAL (cellActivated(int, int)), this, SLOT (cellEnter(int, int)));

        inventory = new Inventory(3, 3);
        dragged_item = NULL;
}
QInvTableWidget::~QInvTableWidget() {
        delete inventory;
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
    //qDebug()<<"TABLE dropEvent";
    //qDebug() << QString(event->mimeData()->text());
    QTableWidget::dropEvent(event);
    for (int i = 0; i < inventory->getRows(); ++i) {
        for (int j = 0; j < inventory->getColumns(); ++j) {
            Item * item = inventory->getItem(i, j);
            if (item != NULL) {
                //qDebug() << item->toString() << ' ';
                qDebug() << i << ':' << j << (item);
            }
        }
    }
    qDebug() << '\n';
}

void QInvTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QTableWidget::dragMoveEvent(event);
}

void QInvTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    //qDebug()<<"TABLE dragEnterEvent";



    event->acceptProposedAction();
    QTableWidget::dragEnterEvent(event);
}


bool QInvTableWidget::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{
    //qDebug()<<"TABLE mime" << row << ' ' << column;
    if(data->hasText())
    {
        QTableWidgetItem *item = this->item(row, column);
        if(item != 0) {
            Item *olditem = new Item(data->text());
            olditem = inventory->addItem(olditem, column, row);
            item->setText(QString::number((olditem->count)));
            QImage image = loadFile(olditem->getImagePath());
            item->setData(Qt::DecorationRole, QPixmap::fromImage(image));
        }
        return false;
    }
    else
    {

        if (dragged_item != NULL) {
            QTableWidgetItem *item = this->item(row, column);
            Item *olditem = inventory->getItem(column, row);
            qDebug() << "no text" << column << row << dragged_item << olditem;
            if ((item != 0) && (olditem != dragged_item)) {
                olditem = inventory->addItem(dragged_item, column, row);
                item->setText(QString::number((olditem->count)));
                QImage image = loadFile(olditem->getImagePath());
                item->setData(Qt::DecorationRole, QPixmap::fromImage(image));
                inventory->delItem(drag_x, drag_y);
            }
        }
        return QTableWidget::dropMimeData(row, column, data, action);
    }
}
// TODO: строить таблицу с изобр и текстом по инвентарю.
// БД. начало игры, сброс-выход. выровнять перетаск.

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
