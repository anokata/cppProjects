#ifndef QINVTABLEWIDGET_H
#define QINVTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QDropEvent>
#include <QImage>
#include <QSound>
#include "inventory.h"
#include "qonecellwidget.h"

const QString appleWav = "./apple-crunch.wav";

class QInvTableWidget : public QOneCellWidget
{
Q_OBJECT
public:
    QInvTableWidget(int rows, int columns, QWidget *parent, QWidget *recipient);
    ~QInvTableWidget();
    void wipeInventory();
    void dropEvent(QDropEvent *event);

public slots:
    void cellStart(int row, int col);
    void passItem(QString path, Item::Item_type type);

signals:
    void itemPassed(QString path, Item::Item_type type);

protected:
    Inventory *inventory;

private:
    bool dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void refreshCells();
    void debug_print_all_items();

};

#endif // QINVTABLEWIDGET_H
