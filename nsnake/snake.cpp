#include "snake.h"
#include "window.h"
#include <ncurses.h>

void Snake::draw(Window *window) {
    // relative win point TODO
    int x = window->left;
    int y = window->top;
    x += segments[0].first;
    y += segments[0].second;
    move(y, x); // Move to head
    //addch(head_char);
    window->putc(head_char, color);
}
