#ifndef ITEM_H
#define ITEM_H
#include <QString>

class Item
{
public:
    enum Item_type { FOOD };
    Item(QString image_path, Item_type type);
    Item(QString image_path, Item_type type, int count);
    QString getImagePath();
    Item_type getType();
    QString toString();
    int count;
    // ID!

private:
    QString image_path;
    Item_type type;

};

#endif // ITEM_H
