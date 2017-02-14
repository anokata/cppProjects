#include "qinvtablewidget.h"

QInvTableWidget::QInvTableWidget(QWidget *parent) : QTableWidget(parent)
{

}

void QInvTableWidget::cellStart(int row, int col) {
    qDebug()<<"TABLE cellStart" << row << ' ' << col;
}

void QInvTableWidget::cellEnter(int row, int col) {
}

QInvTableWidget::QInvTableWidget(int rows, int columns, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{
        setDragEnabled(true);
        setDragDropOverwriteMode(true);
        setDragDropMode(QAbstractItemView::DragDrop);
        setDefaultDropAction(Qt::CopyAction);

        connect(this, SIGNAL (cellPressed(int, int)), this, SLOT (cellStart(int, int)));
        connect(this, SIGNAL (cellActivated(int, int)), this, SLOT (cellEnter(int, int)));
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


bool QInvTableWidget::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{
    qDebug()<<"TABLE mime" << row << ' ' << column;
    if(data->hasText())
    {
        Item *ii = new Item(data->text());

        QTableWidgetItem *item = this->item(row, column);
        if(item != 0) {
            item->setText(QString::number((ii->count)));
            QImage image = loadFile(ii->getImagePath());
            item->setData(Qt::DecorationRole, QPixmap::fromImage(image));
        }
        return false;
    }
    else
    {
        return QTableWidget::dropMimeData(row, column, data, action);
    }
}
