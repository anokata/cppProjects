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


void Snake::move() {
    int lx, ly;
    lx = segments[0].first;
    ly = segments[0].second;
    switch (direction) {
        case Direction::Up:
            segments[0].second--;
            break;
        case Direction::Down:
            segments[0].second++;
            break;
        case Direction::Left:
            segments[0].first--;
            break;
        case Direction::Right:
            segments[0].first++;
            break;
    }
    
    for (auto it = ++segments.begin(); it != segments.end(); ++it) {
        int tx = it->first;
        int ty = it->second;
        it->first = lx;
        it->second = ly;
        lx = tx;
        ly = ty;
    }
}
