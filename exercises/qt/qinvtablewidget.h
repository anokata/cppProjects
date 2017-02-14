#ifndef QINVTABLEWIDGET_H
#define QINVTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QDropEvent>
#include <QDebug>
#include <QImageReader>
#include <QImage>
#include "item.h"
#include "inventory.h"
#include <QHeaderView>

class QInvTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit QInvTableWidget(QWidget *parent = 0);
    QInvTableWidget(int rows, int columns, QWidget *parent = 0);
    ~QInvTableWidget();
    void dropEvent(QDropEvent *event);
    bool dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    QImage loadFile(const QString &fileName);
    void refreshCells();
    void wipeInventory();

signals:
    void itemPassed(Item * item);

public slots:
    void cellStart(int row, int col);
    void cellEnter(int row, int col);
    void passItem(Item * item);

protected:
    Inventory *inventory;
private:
    Item * dragged_item;
    int drag_x;
    int drag_y;
};

#endif // QINVTABLEWIDGET_H
