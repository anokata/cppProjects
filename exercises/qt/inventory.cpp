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
    fromDB();
}

Inventory::~Inventory() {
    db.close();
    QSqlDatabase::removeDatabase("inventory.db");
}

void Inventory::fromDB() {
    deleteItems();
    QSqlQuery query(db);

    query.exec("select X, Y, Count, Type, ImagePath from Inventory \
                inner join Items where Inventory.ItemID = Items.ItemID");
    while (query.next()) { 
        int x = query.value(0).toInt(); 
        int y = query.value(1).toInt(); 
        int count = query.value(2).toInt(); 
        Item::Item_type type = (Item::Item_type) query.value(3).toInt(); 
        QString img_path = query.value(4).toString(); 
        // createItem()
        Item * item = new Item(img_path, type, count);
        items[x][y] = item;
        //qDebug() << x << y << count << type << img_path;
    }
    qDebug() << Item::FOOD;
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

Item * Inventory::appendItem(Item * item, int col, int row) {
    qDebug() << "APPEND ";
    QSqlQuery query(db);
    query.prepare("select Count, Type, ImagePath from Inventory \
                inner join Items where Inventory.ItemID = Items.ItemID \
                and X= :col and Y= :row");
    query.bindValue(":col", col);
    query.bindValue(":row", row);
    query.exec();
    if (query.next()) {
        int count = query.value(0).toInt(); 
        Item::Item_type type = (Item::Item_type) query.value(1).toInt(); 
        QString img_path = query.value(2).toString(); 
        Item * oldItem = new Item(img_path, type, count);
        // type == ?
        item->count += oldItem->count;
        // update item in items
    } else {
        qDebug() << "try INSERT";
        QSqlQuery query(db);
        db.transaction();
        query.prepare("INSERT INTO Items (ItemID, Name, Count, Type, ImagePath) "
                "VALUES (null, :name, :count, :type, :path)");
        query.bindValue(":name", "apple"); 
        query.bindValue(":count", item->count); 
        query.bindValue(":type", item->getType()); 
        query.bindValue(":path", item->getImagePath()); 
        query.exec();
        //qDebug() << "exec" << query.exec() << query.lastQuery();
        int lastid = query.lastInsertId().toInt();
        qDebug() << "inserted item ID:"<< query.lastInsertId().toInt();
        //qDebug() << db.lastError().text();
        db.commit();
        db.transaction();
        query.prepare("INSERT INTO Inventory VALUES (:iid, :x, :y)");
        query.bindValue(":iid", lastid); 
        query.bindValue(":x", col); 
        query.bindValue(":y", row); 
        query.exec();
        db.commit();
        qDebug() << "END INSERT" << db.lastError().text();
    }

}

void Inventory::delItem(int col, int row) {
    items[col][row] = NULL;
}
