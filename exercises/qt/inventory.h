#ifndef INVENTORY_H
#define INVENTORY_H

#include <QVector>
#include <QDebug>
#include "item.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Inventory
{
public:
    Inventory(int cols, int rows);
    ~Inventory();
    Item * getItem(int x, int y);
    int getColumns();
    int getRows();
    Item * addItem(Item * item, int col, int row);
    void delItem(int col, int row);
    void deleteItems();
private:
    QVector< QVector<Item*> > items;
    QSqlDatabase db;

};

#endif // INVENTORY_H
