#include "item.h"
#include <QStringList>

Item::Item(int id, QString image_path, Item_type type) :
    image_path(image_path), type(type), ID(id)
{
    count = 1;
}

Item::Item(int id, QString image_path, Item_type type, int count) :
    image_path(image_path), type(type), count(count), ID(id)
{
}

Item::Item(int id, QString item_string) { // For test only
    QStringList list = item_string.split(":");
    image_path = QString(list.at(2));
    type = (Item::Item_type) list.at(1).toInt();
    count = list.at(0).toInt();
    ID = id;
}

int Item::getId() {
    return ID;
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
