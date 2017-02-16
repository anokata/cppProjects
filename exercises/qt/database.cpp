#include "database.h"

DataBase::DataBase(QString dbName)
{
    this->dbName = dbName;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName); 
    
    if (!db.open()) {
        qDebug() << "db not ok" << db.lastError().text();
    }
}

DataBase::~DataBase()
{
    db.close();
    QSqlDatabase::removeDatabase(dbName);
}

QSqlQuery DataBase::getAllItems()
{
    db = QSqlDatabase::database(dbName);
    QSqlQuery query(db);
    query.exec("select X, Y, Count, Type, ImagePath, Items.ItemID "
               "from Inventory inner join Items "
               "where Inventory.ItemID = Items.ItemID");
    return query;
}

void DataBase::wipeDB()
{
    db = QSqlDatabase::database(dbName);
    QSqlQuery query(db);
    db.transaction();
    query.exec("delete from inventory");
    db.commit();
    query.finish();
    db.transaction();
    query.exec("delete from items");
    db.commit();
    query.finish();
}

void DataBase::deleteById(int id)
{
    QSqlQuery query(db);
    db.transaction();
    query.prepare("delete from inventory where ItemID = :id");
    query.bindValue(":id", id);
    query.exec();
    db.commit();
    query.finish();
}

QSqlQuery DataBase::itemAtCell(int col, int row)
{
    db = QSqlDatabase::database(dbName);
    QSqlQuery query(db);
    query.prepare("select Count, Items.ItemID, Type, ImagePath from Inventory "
                "inner join Items where Inventory.ItemID = Items.ItemID "
                "and X = :col and Y = :row");
    query.bindValue(":col", col);
    query.bindValue(":row", row);
    query.exec();
    return query;
}

void DataBase::updateItemCount(int id, int newCount)
{
    QSqlQuery query(db);
    db.transaction();
    query.prepare("UPDATE Items SET Count = :count WHERE ItemID = :id ");
    query.bindValue(":id", id);
    query.bindValue(":count", newCount);
    query.exec();
    db.commit();
}

void DataBase::addInventoryItem(int id, int col, int row)
{
    db = QSqlDatabase::database(dbName);
    QSqlQuery query(db);
    db.transaction();
    query.prepare("INSERT INTO Inventory VALUES (:iid, :x, :y)");
    query.bindValue(":iid", id); 
    query.bindValue(":x", col); 
    query.bindValue(":y", row); 
    query.exec();
    db.commit();
    query.finish();
}

int DataBase::addNewItem(QString name, int count, ItemType type, QString path)
{
    db = QSqlDatabase::database(dbName);
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
    int last = query.lastInsertId().toInt();
    query.finish();
    return last;
}

void DataBase::deleteByIdItem(int id)
{
    db = QSqlDatabase::database(dbName);
    QSqlQuery query(db);
    db.transaction();
    query.prepare("delete from items where ItemID = :id");
    query.bindValue(":id", id);
    query.exec();
    db.commit();
    query.finish();
}