#include "qonecellwidget.h"

QOneCellWidget::QOneCellWidget(QWidget *parent) : QTableWidget(1, 1, parent)
{
    connect(this, SIGNAL (cellPressed(int, int)), this, SLOT (cellStart(int, int)));
    configure();
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(Qt::DecorationRole, QPixmap::fromImage(loadFile("./apple.jpg")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    this->setItem(0, 0, item);
}

void QOneCellWidget::configure() {
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalHeader()->setResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(120);
    horizontalHeader()->setDefaultSectionSize(120);
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
}

void QOneCellWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QTableWidget::mousePressEvent(event);
        // emit new item dragged
        emit itemPassed(QString("./apple.jpg"), Item::FOOD);
    }
}

QImage QOneCellWidget::loadFile(const QString &fileName) {
    QImageReader reader(fileName);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        qDebug() << "Can not load file";
        return newImage;
    }
    return newImage;
}

void QOneCellWidget::dragEnterEvent(QDragEnterEvent *event)
{
}
