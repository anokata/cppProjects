#ifndef QONECELLWIDGET_H
#define QONECELLWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include "item.h"
#include <QDebug>
#include <QMouseEvent>

class QOneCellWidget : public QTableWidget
{
Q_OBJECT
public:
    QOneCellWidget(QWidget *parent);
    ~QOneCellWidget() {};
    QOneCellWidget(int rows, int columns, QWidget *parent);
    void mousePressEvent(QMouseEvent *event);
    void configure();
public slots:
    void cellStart(int row, int col);

signals:
    void itemPassed(QString, Item::Item_type);

protected:
    Item * dragged_item;
    int drag_x;
    int drag_y;
};

#endif // QONECELLWIDGET_H
