#pragma once
#include <ncurses.h>
#include <string>
#include "color.h"

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
    void putc(char c, int color, int attr);
    void putcxy(char c, int color, int x, int y);
    /* colors */
    void print(std::string str, Color color);
    void putc(char c, Color color);
    void putcxy(char c, Color color, int x, int y);
};
