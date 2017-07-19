#include "man.h"

void Man::draw(Window *window) {
    window->print(symbol, color, x, y);
}

void Man::draw_info(Window *window) {
    std::stringstream fmt;
    fmt << this->x << " " << this->y;
    window->print(fmt.str().c_str(), color::nwhite, 1, 22);
}

void Man::move(Direction direction, CharMap dots) {
    coord x = new_x(direction);
    coord y = new_y(direction);
    if (can_go(x, y, dots)) {
        this->x = x;
        this->y = y;
    }
}

/* private */

bool Man::can_go(coord x, coord y, CharMap dots) {
    char map_char = dots[Point(x, y)];
    if (map_char == '#') {
        return false;
    }
    return true;
}

coord Man::new_x(Direction direction) {
    switch (direction) {
        case Direction::Left:
        case Direction::UpLeft:
        case Direction::DownLeft:
            return x - 1;
            break;
        case Direction::Right:
        case Direction::UpRight:
        case Direction::DownRight:
            return x + 1;
            break;
        default:
            return x;
    }
}

coord Man::new_y(Direction direction) {
    switch (direction) {
        case Direction::Up:
        case Direction::UpLeft:
        case Direction::UpRight:
            return y - 1;
            break;
        case Direction::Down:
        case Direction::DownLeft:
        case Direction::DownRight:
            return y + 1;
            break;
        default:
            return y;
    }
}
