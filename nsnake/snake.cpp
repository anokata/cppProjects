#include "snake.h"
#include "window.h"
#include <ncurses.h>
#include <cmath>


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

int Snake::get_next_x() {
    int nx = segments[0].first;
    switch (direction) {
        case Direction::Left:
            nx--;
            break;
        case Direction::Right:
            nx++;
            break;
    }
    return nx;
}

int Snake::get_next_y() {
    int ny = segments[0].second;
    switch (direction) {
        case Direction::Up:
            ny--;
            break;
        case Direction::Down:
            ny++;
            break;
    }
    return ny;
}


void Snake::move() {
    int lx = segments[0].first;
    int ly = segments[0].second;
    int nx = get_next_x();
    int ny = get_next_y();

    // nx = nx % window->width... TODO
    nx = nx % max_x;
    if (nx < 0) {
        nx = max_x - 1;
    }
    ny = ny % max_y;
    if (ny < 0) {
        ny = max_y - 1;
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

void Snake::turn_back() {
    direction = opposite(direction);
}

void Snake::self_bounce() {
    int nx = get_next_x();
    int ny = get_next_y();
    // TODO
    // How handle this situation?
    // First when? When head is moved on body or before.
    // If after then need back move and what next? head on body?
    // If before then need first know when head will be - duplicate moving logic?
    for (int i = 1; i < segments.size(); i++) {
        int x = segments[i].first;
        int y = segments[i].second;
        if ((x == nx) && (y == ny)) {
            turn_back();
            break;
        }
    }
}

Direction Snake::opposite(Direction direction) {
    if (direction == Direction::Left) return Direction::Right;
    if (direction == Direction::Right) return Direction::Left;
    if (direction == Direction::Up) return Direction::Down;
    if (direction == Direction::Down) return Direction::Up;
}
