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
        Item * item = new Item(id, img_path, type, count);
        items[x][y] = item;
        //qDebug() << x << y << count << type << img_path;
    }
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

void Inventory::appendItem(Item * item, int col, int row) {
    auto query = itemAtCell(col, row);
    if (query.next()) {
        // Куда ложим уже есть предмет. Обновим количество.
        int count = query.value(0).toInt(); 
        int id = query.value(1).toInt(); 
        if (id == item->getId()) {
            // не обрабатывать на себе
            return;
        }
        updateItemCount(id, count + item->getCount());

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
            int lastid = addNewItem("apple", item->getCount(), item->getType(), item->getImagePath());
            addInventoryItem(lastid, col, row);
        }
    }
}

bool Inventory::eatItem(int col, int row) {
    auto query = itemAtCell(col, row);
    if (query.next()) {
        int count = query.value(0).toInt(); 
        int id = query.value(1).toInt(); 
        if (count == 1) {
            deleteById(id);
            deleteByIdItem(id);
        } else {
            updateItemCount(id, count - 1);
        }
        return true;
    }
    return false;
}
