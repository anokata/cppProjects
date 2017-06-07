#include "snake.h"
#include "window.h"
#include <ncurses.h>

void Snake::draw(Window *window) {
    int cx = window->left;
    int cy = window->top;
    int x, y;
    for (auto segment : segments) {
        x = cx + segment.first;
        y = cy + segment.second;
        window->putcxy(body_char, color, x, y);
    }
}
