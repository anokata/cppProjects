#include "item.h"

// TODO? From string
Item::Item(QString image_path, Item_type type) :
    image_path(image_path), type(type)
{
    count = 1;
}

Item::Item(QString image_path, Item_type type, int count) :
    image_path(image_path), type(type)
{
}

QString Item::getImagePath() {
    return image_path;
}

Item::Item_type Item::getType(){
    return type;
}

QString Item::toString() {
    return QString::number(count) + ":" + QString::number(type) + ":" + image_path;
}
