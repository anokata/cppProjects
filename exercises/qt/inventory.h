#ifndef INVENTORY_H
#define INVENTORY_H

#include <QVector>
#include <QDebug>
#include "item.h"

class Inventory
{
public:
    Inventory(int cols, int rows);
    Item * getItem(int x, int y);
    int getColumns();
    int getRows();
    Item * addItem(Item * item, int col, int row);
    void delItem(int col, int row);
private:
    QVector< QVector<Item*> > items;

};

#endif // INVENTORY_H
