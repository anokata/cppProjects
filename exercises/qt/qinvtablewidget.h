#ifndef QINVTABLEWIDGET_H
#define QINVTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QDropEvent>
#include <QDebug>
#include <QImageReader>
#include <QImage>
#include "item.h"

class QInvTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit QInvTableWidget(QWidget *parent = 0);
    QInvTableWidget(int rows, int columns, QWidget *parent = 0);
    void dropEvent(QDropEvent *event);
    bool dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    QImage loadFile(const QString &fileName);

signals:


public slots:
    void cellStart(int row, int col);
    void cellEnter(int row, int col);
};

#endif // QINVTABLEWIDGET_H
