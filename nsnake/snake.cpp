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
    int nx = lx;
    int ny = ly;

    switch (direction) {
        case Direction::Up:
            ny--;
            break;
        case Direction::Down:
            ny++;
            break;
        case Direction::Left:
            nx--;
            break;
        case Direction::Right:
            nx++;
            break;
    }
    if (is_growth) {
        segments.insert(segments.begin(), Point(nx, ny));
        is_growth = false;
    } else {
        segments[0].first = nx;
        segments[0].second = ny;
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

void Snake::growth() {
    is_growth = true;
}
