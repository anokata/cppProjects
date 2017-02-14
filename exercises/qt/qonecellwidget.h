#ifndef QONECELLWIDGET_H
#define QONECELLWIDGET_H

#include <QWidget>
#include "qinvtablewidget.h"

class QOneCellWidget : public QInvTableWidget
{
public:
    QOneCellWidget(QWidget *parent);
    void mousePressEvent(QMouseEvent *event);
public slots:
    void cellStart(int row, int col);
};

#endif // QONECELLWIDGET_H
