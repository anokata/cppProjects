#ifndef QONECELLWIDGET_H
#define QONECELLWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QImage>

class QOneCellWidget : public QTableWidget
{
public:
    explicit QOneCellWidget(QWidget *parent, QImage image);
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
private:
    QImage dragImage;
};

#endif // QONECELLWIDGET_H
