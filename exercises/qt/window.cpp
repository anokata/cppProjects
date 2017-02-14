#include "window.h"
#include <QPushButton>
#include <QFont>
#include <QApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QDir>


Window::Window(QWidget *parent) : QWidget(parent)
{
    setFixedSize(500, 550);
    setGeometry(0, 0, 500, 500);

    //QFont font("DejaVu Sans Mono");
    //exit_button->setFont(font);
    //inventory = new Inventory(this);
    //inventory->setGeometry(10, 100, 200, 200);
    inventory = new QTableWidget(3, 3, this);
    inventory->horizontalHeader()->hide();
    inventory->verticalHeader()->hide();
    inventory->setGeometry(10, 100, 300, 300);
    inventory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    inventory->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    inventory->verticalHeader()->setDefaultSectionSize(80);
    inventory->horizontalHeader()->setDefaultSectionSize(80);
    exit_button = new QPushButton(tr("xit"), this);
    exit_button->setGeometry(10, 10, 80, 30);
    exit_button->setLayoutDirection(Qt::RightToLeft);
    connect(exit_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));

    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setText("asd");
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setGeometry(400, 200, 100, 100);
    loadFile("./apple.png");
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
    imageLabel->adjustSize();
    image = newImage;
    return true;
}

