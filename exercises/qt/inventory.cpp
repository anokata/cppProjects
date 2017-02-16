#include "inventory.h"

Inventory::Inventory(int cols, int rows)
{
    items = QVector< QVector<Item*> >(rows);
    for (int i = 0; i < rows; ++i) {
        items[i] = QVector<Item*>(cols);
    }

    dataBase = new DataBase(QString("inventory.db"));
    fromDB();
}

Inventory::~Inventory()
{
    delete dataBase;
}

void Inventory::wipeDB() {
    dataBase->wipeDB();
    fromDB();
}

void Inventory::fromDB()
{
    deleteItems();

    QSqlQuery query = dataBase->getAllItems();
    while (query.next()) { 
        int x = query.value(0).toInt(); 
        int y = query.value(1).toInt(); 
        int count = query.value(2).toInt(); 
        Item_type type = (Item_type) query.value(3).toInt(); 
        QString img_path = query.value(4).toString(); 
        int id = query.value(5).toInt(); 
        Item * item = new Item(id, img_path, type, count);
        items[x][y] = item;
        //qDebug() << x << y << count << type << img_path;
    }
}

Item * Inventory::getItem(int x, int y)
{
    return (items[x][y]);
}

int Inventory::getColumns()
{
    return items[0].size();
}

int Inventory::getRows()
{
    return items.size();
}

void Inventory::deleteItems()
{
    for (int i = 0; i < items.size(); ++i) {
        for (int j = 0; j < items[i].size(); ++j) {
            delete items[i][j];
            items[i][j] = NULL;
        }
    }
}

void Inventory::moveItem(Item * item, int col, int row)
{
    auto query = dataBase->itemAtCell(col, row);
    if (query.next()) {
        // Куда ложим уже есть предмет. Обновим количество.
        int count = query.value(0).toInt(); 
        int id = query.value(1).toInt(); 
        if (id == item->getId()) {
            // не обрабатывать на себе
            return;
        }
        dataBase->updateItemCount(id, count + item->getCount());

        if (item->getId() != -1) {
            // Если ложимый предмет был не новый удалим его со старого места
            dataBase->deleteById(item->getId());
            // И удалим со старым значением сам предмет TODO
            dataBase->deleteByIdItem(item->getId());
        }
    } else { 
        // Ложим на пустую ячейку
        if (item->getId() != -1) {
            // Ложим не новый предмет - удалим сначала со старого места
            dataBase->deleteById(item->getId());
            dataBase->addInventoryItem(item->getId(), col, row);
        } else {
            // создаём новый предмет в пустой ячейке
            int lastid = dataBase->addNewItem("apple", item->getCount(), item->getType(), item->getImagePath());
            dataBase->addInventoryItem(lastid, col, row);
        }
    }
}

bool Inventory::eatItem(int col, int row)
{
    auto query = dataBase->itemAtCell(col, row);
    if (query.next()) {
        int count = query.value(0).toInt(); 
        int id = query.value(1).toInt(); 
        if (count == 1) {
            dataBase->deleteById(id);
            dataBase->deleteByIdItem(id);
        } else {
            dataBase->updateItemCount(id, count - 1);
        }
        return true;
    }
    return false;
}
