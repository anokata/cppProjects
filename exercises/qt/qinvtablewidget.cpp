#include "qinvtablewidget.h"

QInvTableWidget::QInvTableWidget(QWidget *parent) : QTableWidget(parent)
{

}


QInvTableWidget::QInvTableWidget(int rows, int columns, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{

}

void QInvTableWidget::dropEvent(QDropEvent *event)
{
    qDebug()<<"TABLE dropEvent";

}
