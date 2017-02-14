#include "qonecellwidget.h"
#include "item.h"
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

QOneCellWidget::QOneCellWidget(QWidget *parent, QImage image) : QTableWidget(parent)
{
    dragImage = image;
    setColumnCount(1);
    setRowCount(1);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalHeader()->setResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(100);
    horizontalHeader()->setDefaultSectionSize(100);
    setDragEnabled(true);
}

void QOneCellWidget::mousePressEvent(QMouseEvent *event) {
    qDebug() << "mpe";
    if (event->button() == Qt::LeftButton) {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        // GEN ITEM
        qDebug() << "QOneCellWidget Start drag";
        Item item("./apple.jpg", Item::FOOD);
        mimeData->setText(item.toString());
        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap::fromImage(dragImage));
        drag->exec();
    }
}

void QOneCellWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}
