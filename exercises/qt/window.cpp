#include "window.h"
#include <QPushButton>
#include <QFont>
#include <QApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QDir>
#include <QMouseEvent>
#include <QDebug>


Window::Window(QWidget *parent) : QWidget(parent)
{
    const int INV_DIMENSION = 3;
    setFixedSize(600, 650);
    setGeometry(0, 0, 600, 600);

    //QFont font("DejaVu Sans Mono");
    //exit_button->setFont(font);
    //= new Inventory(this);
    inventory = new QInvTableWidget(INV_DIMENSION, INV_DIMENSION, this);
    inventory->horizontalHeader()->hide();
    inventory->verticalHeader()->hide();
    inventory->setGeometry(10, 100, 400, 400);
    inventory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    inventory->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    inventory->verticalHeader()->setDefaultSectionSize(100);
    inventory->horizontalHeader()->setDefaultSectionSize(100);
    exit_button = new QPushButton(tr("xit"), this);
    exit_button->setGeometry(10, 10, 80, 30);
    exit_button->setLayoutDirection(Qt::RightToLeft);
    connect(exit_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));

    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setText("asd");
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setGeometry(450, 200, 100, 100);
    loadFile("./apple.jpg");

    inventory->setDragEnabled(true);
    for (int i = 0; i < INV_DIMENSION; ++i) {
        for (int j = 0; j < INV_DIMENSION; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem;
            inventory->setItem(i, j, item);
        }
    }

    //inventory->item(0, 1)->setData(Qt::DecorationRole, QPixmap::fromImage(image));

    inventory->setAcceptDrops(true); //?
    setAcceptDrops(true);

}

bool Window::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, "_",
               tr("Cannot load %1: %2")
               .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }
    imageLabel->setPixmap(QPixmap::fromImage(newImage));
    //imageLabel->adjustSize();
    image = newImage;
    return true;
}

void Window::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton
        && imageLabel->geometry().contains(event->pos())) {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setImageData(image);
        drag->setMimeData(mimeData);
        drag->setPixmap(*imageLabel->pixmap());

        Qt::DropAction dropAction = drag->exec();

    }
}

void Window::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"dragEnterEvent";
    event->acceptProposedAction();
}

void Window::dropEvent(QDropEvent *event)
{
    qDebug()<<"dropEvent";
    if (inventory->geometry().contains(event->pos())) {
        //inventory->item()
        inventory->item(0, 0)->setData(Qt::DecorationRole, QPixmap::fromImage(image));

        event->acceptProposedAction();
    } else {
        qDebug()<<"not in inv drop";
    }
}

