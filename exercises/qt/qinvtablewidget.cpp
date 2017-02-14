#include "qinvtablewidget.h"

QInvTableWidget::QInvTableWidget(QWidget *parent) : QTableWidget(parent)
{}

void QInvTableWidget::cellStart(int row, int col) {
    dragged_item = inventory->getItem(col, row);
    qDebug()<<"TABLE cellStart" << row << col << "COUTN" << (dragged_item!=NULL?dragged_item->count:0);
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
    qDebug()<<"TABLE dropEvent";
    qDebug() << QString(event->mimeData()->text());
    QTableWidget::dropEvent(event);
    for (int i = 0; i < inventory->getRows(); ++i) {
        for (int j = 0; j < inventory->getColumns(); ++j) {
            Item * item = inventory->getItem(i, j);
            if (item != NULL) {
                //qDebug() << item->toString() << ' ';
                qDebug() << i << ':' << j << (item) << item->count;
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

void QInvTableWidget::refreshCells() {
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
    if(data->hasText())
    {
        QTableWidgetItem *item = this->item(row, column);
        if(item != 0) {
            qDebug()<<"TABLE mime" << row << ' ' << column << data->text();
            Item *olditem = new Item(data->text());
            olditem = inventory->addItem(olditem, column, row);
        }
    }
    else
    {
        if (dragged_item != NULL) {
            QTableWidgetItem *item = this->item(row, column);
            Item *olditem = inventory->getItem(column, row);
            qDebug() << "no text" << column << row << dragged_item << olditem;
            if ((item != 0) && (olditem != dragged_item)) {
                olditem = inventory->addItem(dragged_item, column, row);
                inventory->delItem(drag_x, drag_y);
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
