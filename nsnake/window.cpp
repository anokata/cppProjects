#include "window.h"

int Window::cl_red = 1;
int Window::cl_blue = 2;
int Window::cl_yellow = 3;

Window::Window(WINDOW *win) {
    getmaxyx(win, height, width);
    this->win = win;
    left = width / 4;
    top = height / 4;

    init_pair (Window::cl_red, COLOR_RED, COLOR_BLACK);
    init_pair (Window::cl_blue, COLOR_BLUE, COLOR_BLACK);
    init_pair (Window::cl_yellow, COLOR_BLUE, COLOR_BLACK);
}

void Window::print(std::string str, int color) {
    attron(COLOR_PAIR(color));
    printw(str.c_str());
}

void Window::putc(char c, int color) {
    attron(A_BOLD);
    attron(COLOR_PAIR(color));
    addch(c);
    attroff(COLOR_PAIR(color));
    attroff(A_BOLD);
}

void Window::putc(char c, int color, int attr) {
    attron(attr);
    attron(COLOR_PAIR(color));
    addch(c);
    attroff(COLOR_PAIR(color));
    attroff(attr);
}

void Window::putcxy(char c, int color, int x, int y) {
    move(y, x);
    putc(c, color);
}
