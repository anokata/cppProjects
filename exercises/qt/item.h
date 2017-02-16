#ifndef ITEM_H
#define ITEM_H
#include <QString>
#include "const.h"

class Item
{
public:
    Item(int id, QString image_path, Item_type type);
    Item(int id, QString image_path, Item_type type, int count);
    QString getImagePath();
    Item_type getType();
    int getId();
    int getCount();

private:
    QString image_path;
    Item_type type;
    int ID;
    int count;

};

#endif // ITEM_H
