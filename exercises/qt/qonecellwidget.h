#ifndef QONECELLWIDGET_H
#define QONECELLWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include "item.h"
#include <QDebug>
#include <QMouseEvent>
#include <QImageReader>

class QOneCellWidget : public QTableWidget
{
Q_OBJECT
public:
    QOneCellWidget(int rows, int columns, QWidget *parent);
    QOneCellWidget(QWidget *parent);
    ~QOneCellWidget() {};

public slots:

signals:
    void itemPassed(QString, Item::Item_type);

protected:
    void mousePressEvent(QMouseEvent *event);
    QImage loadFile(const QString &fileName);
    void dragEnterEvent(QDragEnterEvent *event);
    void configure();

    Item * dragged_item;
};

#endif // QONECELLWIDGET_H
