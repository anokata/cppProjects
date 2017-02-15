#include "window.h"
#include <QPushButton>
#include <QFont>
#include <QApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QDir>
#include <QMouseEvent>
#include <QDebug>

// TODO: строить таблицу с изобр и текстом по инвентарю.
// БД. начало игры, сброс-выход. выровнять перетаск.
// сделать генератор тоже обычной таблицей с одной ячейкой. наследовать.
// unicode
// private методы убрать, задать интерфейс.
// comments to methods. ui create
// давай сделаем так: одноячейковый тейбл будет получать виджет в который будет в спец
// слот соединять сигнал по которому передавать данные об новом объекте. пре mousePress..
// будем генерить итем и эмитить сигнал
// сделать чтобы одноячейковый не принимал и не перерисовался?
// Съедать + звук
Window::Window(QWidget *parent) : QWidget(parent)
{
    const int INV_DIMENSION = 3;
    setFixedSize(600, 650);
    setGeometry(0, 0, 600, 600);

    //QFont font("DejaVu Sans Mono");
    //exit_button->setFont(font);
    //= new Inventory(this);
    oneItem = new QOneCellWidget(this);
    oneItem->setGeometry(450, 300, 100, 100);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(Qt::DecorationRole, QPixmap::fromImage(inventoryWidget->loadFile("./apple.jpg")));
    oneItem->setItem(0, 0, item);

    inventoryWidget = new QInvTableWidget(INV_DIMENSION, INV_DIMENSION, this, oneItem);
    inventoryWidget->setGeometry(10, 100, 400, 400);
    //configureTableWidget(inventoryWidget);

    exit_button = new QPushButton(tr("xit"), this);
    exit_button->setGeometry(10, 10, 80, 30);
    exit_button->setLayoutDirection(Qt::RightToLeft);
    connect(exit_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
    newgame_button = new QPushButton(tr("New"), this);
    newgame_button->setGeometry(110, 10, 80, 30);
    connect(newgame_button, SIGNAL (clicked()), this, SLOT (newgame()));

    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setText("asd");
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setGeometry(450, 200, 100, 100);
    imageLabel->setPixmap(QPixmap::fromImage(inventoryWidget->loadFile("./apple.jpg")));

    for (int i = 0; i < INV_DIMENSION; ++i) {
        for (int j = 0; j < INV_DIMENSION; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem;
            inventoryWidget->setItem(i, j, item);
        }
    }


    inventoryWidget->setAcceptDrops(true);
    setAcceptDrops(true);
}

void Window::newgame() {
    qDebug() << "new";
    inventoryWidget->wipeInventory();
}

Window::~Window() {
    delete inventoryWidget;
    delete imageLabel;
    delete exit_button;
    delete oneItem;
}

void Window::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton
        && imageLabel->geometry().contains(event->pos())) {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        //mimeData->setImageData(image);
        // GEN ITEM
        qDebug() << "WINDOW Start drag";
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
    if (inventoryWidget->geometry().contains(event->pos())) {
        event->acceptProposedAction();
    }
}

void Window::dropEvent(QDropEvent *event)
{
    if (inventoryWidget->geometry().contains(event->pos())) {
        inventoryWidget->dropEvent(event);
    } else {
        qDebug()<<"miss drop";
    }
}

