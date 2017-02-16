#include "item.h"
#include <QStringList>

Item::Item(int id, QString imagePath, ItemType type) :
    imagePath(imagePath), type(type), ID(id)
{
    count = 1;
}

Item::Item(int id, QString imagePath, ItemType type, int count) :
    imagePath(imagePath), type(type), count(count), ID(id)
{ }

int Item::getCount() {
    return count;
}

int Item::getId() {
    return ID;
}

QString Item::getImagePath() {
    return imagePath;
}

ItemType Item::getType(){
    return type;
}

