#include "object.h"

void Object::draw(Window *window) {
    int x = window->left + this->x;
    int y = window->top + this->y;
    window->putcxy(chr, color, x, y);
}
