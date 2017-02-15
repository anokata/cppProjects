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
    void fromDB();
    void wipeDB();
    void appendItem(Item * item, int col, int row);
    bool eatItem(int col, int row);
    int getColumns();
    int getRows();

private:
    void deleteItems();

    QSqlQuery itemAtCell(int col, int row);
    void deleteById(int id);
    void updateItemCount(int id, int newCount);
    void addInventoryItem(int id, int row, int col);
    int addNewItem(QString name, int count, Item::Item_type type, QString path);
    void deleteByIdItem(int id);

    QVector< QVector<Item*> > items;
    QSqlDatabase db;

};

#endif // INVENTORY_H
