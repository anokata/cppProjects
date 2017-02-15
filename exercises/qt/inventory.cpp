#include "inventory.h"

Inventory::Inventory(int cols, int rows)
{
    items = QVector< QVector<Item*> >(rows);
    for (int i = 0; i < rows; ++i) {
        items[i] = QVector<Item*>(cols);
    }

    db = QSqlDatabase::addDatabase("QSQLITE", "inventory.db");
    db.setDatabaseName("inventory.db"); 
    
    if (!db.open()) {
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

    query.exec("select X, Y, Count, Type, ImagePath, Items.ItemID from Inventory \
                inner join Items where Inventory.ItemID = Items.ItemID");
    while (query.next()) { 
        int x = query.value(0).toInt(); 
        int y = query.value(1).toInt(); 
        int count = query.value(2).toInt(); 
        Item::Item_type type = (Item::Item_type) query.value(3).toInt(); 
        QString img_path = query.value(4).toString(); 
        int id = query.value(5).toInt(); 
        // createItem() TODO in DB
        Item * item = new Item(id, img_path, type, count);
        items[x][y] = item;
        qDebug() << x << y << count << type << img_path;
    }
}

void Inventory::wipeDB() {
    QSqlQuery query(db);
    db.transaction();
    query.exec("delete from inventory");
    db.commit();
    db.transaction();
    query.exec("delete from items");
    db.commit();
    fromDB();
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

/*Item * Inventory::addItem(Item * item, int col, int row) {
    if (items[col][row] == NULL) {
        qDebug() << "=item";
        items[col][row] = item;
    } else {
        qDebug() << "+item";
        items[col][row]->count += item->count;
        delete item;
    }
    return items[col][row];
}*/

void Inventory::deleteById(int id) {
    QSqlQuery query(db);
    db.transaction();
    query.prepare("delete from inventory where ItemID = :id");
    query.bindValue(":id", id);
    query.exec();
    db.commit();
}

QSqlQuery Inventory::itemAtCell(int col, int row) {
    QSqlQuery query(db);
    query.prepare("select Count, Items.ItemID, Type, ImagePath from Inventory "
                "inner join Items where Inventory.ItemID = Items.ItemID "
                "and X = :col and Y = :row");
    query.bindValue(":col", col);
    query.bindValue(":row", row);
    query.exec();
    return query;
}

void Inventory::updateItemCount(int id, int newCount) {
    QSqlQuery quer_upd(db);
    db.transaction();
    quer_upd.prepare("UPDATE Items SET Count = :count WHERE ItemID = :id ");
    quer_upd.bindValue(":id", id); 
    quer_upd.bindValue(":count", newCount); 
    quer_upd.exec();
    //qDebug() << "update item ID" << id << "count" << count << item->count << count + item->count;
    //qDebug() << db.lastError().text();
    db.commit();
}

void Inventory::addInventoryItem(int id, int col, int row) {
    QSqlQuery query(db);
    db.transaction();
    query.prepare("INSERT INTO Inventory VALUES (:iid, :x, :y)");
    query.bindValue(":iid", id); 
    query.bindValue(":x", col); 
    query.bindValue(":y", row); 
    query.exec();
    db.commit();
}

int Inventory::addNewItem(QString name, int count, Item::Item_type type, QString path) {
    QSqlQuery query(db);
    db.transaction();
    query.prepare("INSERT INTO Items (ItemID, Name, Count, Type, ImagePath) "
            "VALUES (null, :name, :count, :type, :path)");
    query.bindValue(":name", name); 
    query.bindValue(":count", count); 
    query.bindValue(":type", type); 
    query.bindValue(":path", path); 
    query.exec();
    db.commit();
    return query.lastInsertId().toInt();
}

void Inventory::deleteByIdItem(int id) {
    QSqlQuery query(db);
    db.transaction();
    query.prepare("delete from items where ItemID = :id");
    query.bindValue(":id", id);
    query.exec();
    db.commit();
}

Item * Inventory::appendItem(Item * item, int col, int row) {
    qDebug() << "APPEND " << item->getId();
    auto query = itemAtCell(col, row);
    if (query.next()) {
        // Куда ложим уже есть предмет. Обновим количество.
        int count = query.value(0).toInt(); 
        int id = query.value(1).toInt(); 
        updateItemCount(id, count + item->count);

        if (item->getId() != -1) {
            // Если ложимый предмет был не новый удалим его со старого места
            deleteById(item->getId());
            // И удалим со старым значением сам предмет TODO
            deleteByIdItem(item->getId());
        }
    } else { 
        // Ложим на пустую ячейку
        if (item->getId() != -1) {
            // Ложим не новый предмет - удалим сначала со старого места
            deleteById(item->getId());
            addInventoryItem(item->getId(), col, row);
        } else {
            // создаём новый предмет в пустой ячейке
            int lastid = addNewItem("apple", item->count, item->getType(), item->getImagePath());
            qDebug() << "inserted item ID:"<< lastid;
            addInventoryItem(lastid, col, row);
        }
    }
}

void Inventory::delItem(int col, int row) {
    items[col][row] = NULL;
}
