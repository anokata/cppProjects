#include "item.h"
#include <QStringList>

Item::Item(int id, QString image_path, Item_type type) :
    image_path(image_path), type(type), ID(id)
{
    count = 1;
}

Item::Item(int id, QString image_path, Item_type type, int count) :
    image_path(image_path), type(type), count(count), ID(id)
{ }

int Item::getCount() {
    return count;
}

int Item::getId() {
    return ID;
}

QString Item::getImagePath() {
    return image_path;
}

Item_type Item::getType(){
    return type;
}

