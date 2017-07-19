#pragma once
#ifndef __MAN_
#define __MAN__

#include "furses/window.h"
#include <sstream>

typedef int coord;

class Man {
    private:
        coord x;
        coord y;

        coord new_x(Direction);
        coord new_y(Direction);
        bool can_go(coord x, coord y);

    public:
        Man(coord x, coord y) : x(x), y(y) {}
        Color color = color::bblue;
        std::string symbol = "@";
        void draw(Window *window);
        void move(Direction direction);
        void draw_info(Window *window);
};

#endif
