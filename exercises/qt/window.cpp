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
    inventoryWidget = new QInvTableWidget(INV_DIMENSION, INV_DIMENSION, this);
    inventoryWidget->horizontalHeader()->hide();
    inventoryWidget->verticalHeader()->hide();
    inventoryWidget->setGeometry(10, 100, 400, 400);
    inventoryWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    inventoryWidget->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    inventoryWidget->verticalHeader()->setDefaultSectionSize(100);
    inventoryWidget->horizontalHeader()->setDefaultSectionSize(100);
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

    inventoryWidget->setDragEnabled(true);
    for (int i = 0; i < INV_DIMENSION; ++i) {
        for (int j = 0; j < INV_DIMENSION; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem;
            inventoryWidget->setItem(i, j, item);
        }
    }

    //inventory->item(0, 1)->setData(Qt::DecorationRole, QPixmap::fromImage(image));

    inventoryWidget->setAcceptDrops(true); //?
    setAcceptDrops(true);

    inventory = new Inventory(3, 3);
    Item *i = new Item("some", Item::FOOD);
    inventory->addItem(i, 0, 0);
}

Window::~Window() {
    delete inventory;
    delete inventoryWidget;
    delete imageLabel;
    delete exit_button;
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

        Item item("./apple.jpg", Item::FOOD);
        mimeData->setText(item.toString());

        drag->setMimeData(mimeData);
        drag->setPixmap(*imageLabel->pixmap());

        drag->exec();
        //Qt::DropAction dropAction = drag->exec();
    }
}

void Window::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"dragEnterEvent";
    event->acceptProposedAction();
}

void Window::dropEvent(QDropEvent *event)
{
    if (inventoryWidget->geometry().contains(event->pos())) {
        //inventory->item()
        inventoryWidget->item(0, 0)->setData(Qt::DecorationRole, QPixmap::fromImage(image));
        inventoryWidget->item(0, 0)->setText("1");
        qDebug() << "drop: " << event->mimeData()->text();
        event->acceptProposedAction();

        for (int i = 0; i < inventory->getRows(); ++i) {
            for (int j = 0; j < inventory->getColumns(); ++j) {
                Item &item = inventory->getItem(i,j);
                if (&item != NULL) {
                    qDebug() << item.toString() << ' ';
                }
            }
            qDebug() << '\n';
        }

    } else {
        qDebug()<<"miss drop";
    }
}

