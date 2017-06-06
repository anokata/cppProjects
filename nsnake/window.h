#pragma once
#include <ncurses.h>

class Window {
    public:
    int width;
    int height;
    WINDOW *win;
    int left;
    int top;

    Window(WINDOW *win);
};
