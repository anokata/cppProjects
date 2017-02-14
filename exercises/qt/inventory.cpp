#include <QTimer>
#include <QPainter>
#include "inventory.h"
#include <QTextStream>

const int INVENTORY_ROWS = 3;
const int INVENTORY_COLS = 3;

Inventory::Inventory(QWidget *parent) : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    resize(300, 300);
}

void Inventory::drawGrid(QPainter *p) {
    const int CELL_SIZE = width() / (INVENTORY_COLS);
    QColor grid_line(0, 0, 127);
    p->setPen(grid_line);
    //p->drawRect(0, 0, width(), height());
    p->setBrush(grid_line);
    for (int x = 0; x <= INVENTORY_COLS; ++x) {
        p->drawLine(x * CELL_SIZE, 0, x * CELL_SIZE, height());
    }
    for (int y = 0; y <= INVENTORY_ROWS; ++y) {
        p->drawLine(width(), y * CELL_SIZE, 0, y * CELL_SIZE);
    }
}

void Inventory::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawGrid(&painter);
}
