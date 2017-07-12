#include "man.h"

void Man::draw(Window *window) {
    window->print(symbol, color, x, y);
}

void Man::draw_info(Window *window) {
    std::stringstream fmt;
    fmt << this->x << " " << this->y;
    window->print(fmt.str().c_str(), color::nwhite, 1, 22);
}

void Man::move(Direction direction) {
    coord x = new_x(direction);
    coord y = new_y(direction);
    if (can_go(x, y)) {
        this->x = x;
        this->y = y;
    }
}

/* private */

bool Man::can_go(coord x, coord y) {
    return true;
}

coord Man::new_x(Direction direction) {
    switch (direction) {
        case Direction::Left:
            return x - 1;
            break;
        case Direction::Right:
            return x + 1;
            break;
        default:
            return x;
    }
}

coord Man::new_y(Direction direction) {
    switch (direction) {
        case Direction::Up:
            return y - 1;
            break;
        case Direction::Down:
            return y + 1;
            break;
        default:
            return y;
    }
}
