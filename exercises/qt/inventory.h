#ifndef INVENTORY_H
#define INVENTORY_H

#include <QVector>
#include <QDebug>
#include "item.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class Inventory
{
public:
    Inventory(int cols, int rows);
    ~Inventory();
    Item * getItem(int x, int y);
    int getColumns();
    int getRows();
    //Item * addItem(Item * item, int col, int row);
    void delItem(int col, int row);
    void deleteItems();
    void fromDB();
    void wipeDB();
    Item * appendItem(Item * item, int col, int row);
private:
    QVector< QVector<Item*> > items;
    QSqlDatabase db;
    void deleteById(int id);
    QSqlQuery itemAtCell(int col, int row);
    void updateItemCount(int id, int newCount);
    void addInventoryItem(int id, int row, int col);

};

#endif // INVENTORY_H
