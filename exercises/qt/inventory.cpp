#include "inventory.h"

Inventory::Inventory(int cols, int rows)
{
    items = QVector< QVector<Item*> >(rows);
    for (int i = 0; i < rows; ++i) {
        items[i] = QVector<Item*>(cols);
    }

    db = QSqlDatabase::addDatabase("QSQLITE", "inventory.db");
    db.setDatabaseName("inventory.db"); 
    
    if (db.open()) {
        qDebug() << "db ok";
    } else {
        qDebug() << "db not ok" << db.lastError().text();
    }
    QSqlQuery query(db);
    query.exec("SELECT * FROM Items");
    while (query.next()) { 
        QString id = query.value(0).toString(); 
        QString name = query.value(1).toString(); 
        qDebug() << id << name;
    }
}

Inventory::~Inventory() {
    db.close();
    //QSqlDatabase::removeDatabase();
}

Item * Inventory::getItem(int x, int y) {
    return (items[x][y]);
}

int Inventory::getColumns() {
    return items[0].size();
}

int Inventory::getRows() {
    return items.size();
}

void Inventory::deleteItems() {
    for (int i = 0; i < items.size(); ++i) {
        for (int j = 0; j < items[i].size(); ++j) {
            delete items[i][j];
            items[i][j] = NULL;
        }
    }
}

Item * Inventory::addItem(Item * item, int col, int row) {
    if (items[col][row] == NULL) {
        qDebug() << "=item";
        items[col][row] = item;
    } else {
        qDebug() << "+item";
        items[col][row]->count += item->count;
        delete item;
    }
    return items[col][row];
}

void Inventory::delItem(int col, int row) {
    items[col][row] = NULL;
}
