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
    setFixedSize(600, 650);
    setGeometry(0, 0, 600, 600);

    //QFont font("DejaVu Sans Mono");
    //exit_button->setFont(font);
    //inventory = new Inventory(this);
    //inventory->setGeometry(10, 100, 200, 200);
    inventory = new QTableWidget(3, 3, this);
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

    QTableWidgetItem *test = new QTableWidgetItem;
    test->setData(Qt::DecorationRole, QPixmap::fromImage(image));
    //qDebug()<<" was  opened!";

    inventory->setItem(0, 0, test);
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

        //mimeData->setText(commentEdit->toPlainText());
        mimeData->setImageData(image);
        drag->setMimeData(mimeData);
        drag->setPixmap(*imageLabel->pixmap());

        Qt::DropAction dropAction = drag->exec();
        qDebug()<<"start drag";
    }
}

void Window::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void Window::dropEvent(QDropEvent *event)
{
    if (inventory->geometry().contains(event->pos())) {
        qDebug()<<"drop";
          QTableWidgetItem *test = new QTableWidgetItem;
        test->setData(Qt::DecorationRole, event->mimeData()->imageData());
        //inventory->item(1, 1)->set
        inventory->setItem(1, 1, test);
        event->acceptProposedAction();
    } else {
        qDebug()<<"not in inv drop";
    }
    //event->mimeData()->



}
