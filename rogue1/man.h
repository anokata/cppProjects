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

        bool can_go(coord x, coord y, CharMap dots);

    public:
        Man(coord x, coord y) : x(x), y(y) {}
        Color color = color::bblue;
        std::string symbol = "@";
        void draw(Window *window);
        void move(Direction direction, CharMap dots);
        void draw_info(Window *window);
        coord getx() { return x; }
        coord gety() { return y; }
        coord new_x(Direction);
        coord new_y(Direction);
};

#endif
