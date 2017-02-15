#ifndef QINVTABLEWIDGET_H
#define QINVTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QDropEvent>
#include <QImageReader>
#include <QImage>
#include "inventory.h"
#include "qonecellwidget.h"

class QInvTableWidget : public QOneCellWidget
{
Q_OBJECT
public:
    QInvTableWidget(int rows, int columns, QWidget *parent, QWidget *recipient);
    ~QInvTableWidget();
    void dropEvent(QDropEvent *event);
    bool dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QImage loadFile(const QString &fileName);
    void refreshCells();
    void wipeInventory();

public slots:
    void cellStart(int row, int col);
    void cellEnter(int row, int col);
    void passItem(QString path, Item::Item_type type);
    void debug_print_all_items();

signals:
    void itemPassed(QString path, Item::Item_type type);

protected:
    Inventory *inventory;
};

#endif // QINVTABLEWIDGET_H
