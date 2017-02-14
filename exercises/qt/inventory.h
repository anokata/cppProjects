#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>

class Inventory : public QWidget
{
    Q_OBJECT
public:
    explicit Inventory(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawGrid(QPainter *p);
};

#endif // INVENTORY_H
