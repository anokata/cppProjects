#include "object.h"

void Object::draw(Window *window) {
    int x = window->left + this->x;
    int y = window->top + this->y;
    char c = frames[frame];
    frame = (frame + 1) % frames.size();
    window->putcxy(c, color, x, y);
}
