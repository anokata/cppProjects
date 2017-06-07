#include "window.h"

int Window::cl_red = 1;

Window::Window(WINDOW *win) {
    getmaxyx(win, height, width);
    this->win = win;
    left = width / 4;
    top = height / 4;

    init_pair (1, COLOR_RED, COLOR_BLACK);
}

void Window::print(std::string str, int color) {
    attron(COLOR_PAIR(color));
    printw(str.c_str());
}

void Window::putc(char c, int color) {
    attron(COLOR_PAIR(color));
    addch(c);
}

void Window::putcxy(char c, int color, int x, int y) {
    move(y, x);
    attron(COLOR_PAIR(color));
    addch(c);
}
