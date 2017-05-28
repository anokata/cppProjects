#pragma once
#include <ncurses.h>

class Window {
    public:
    int width;
    int height;
    WINDOW *win;

    Window(WINDOW *win);
};
