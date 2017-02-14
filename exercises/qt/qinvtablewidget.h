#ifndef QINVTABLEWIDGET_H
#define QINVTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QDropEvent>
#include <QDebug>

class QInvTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit QInvTableWidget(QWidget *parent = 0);
    QInvTableWidget(int rows, int columns, QWidget *parent = 0);
    void dropEvent(QDropEvent *event);

signals:

public slots:
};

#endif // QINVTABLEWIDGET_H
