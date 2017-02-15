#ifndef ITEM_H
#define ITEM_H
#include <QString>

class Item
{
public:
    enum Item_type { FOOD };
    Item(int id, QString image_path, Item_type type);
    Item(int id, QString image_path, Item_type type, int count);
    Item(int id, QString item_string);
    QString getImagePath();
    Item_type getType();
    int getId();
    QString toString();
    int count;
    int ID;

private:
    QString image_path;
    Item_type type;

};

#endif // ITEM_H
