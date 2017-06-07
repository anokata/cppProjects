#pragma once
#include <ncurses.h>
#include <string>

class Window {
    public:
    int width;
    int height;
    WINDOW *win;
    int left;
    int top;

    Window(WINDOW *win);
    void print(std::string str, int color);
    void putc(char c, int color);
    void putcxy(char c, int color, int x, int y);
    static int cl_red;
};
