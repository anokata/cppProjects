#include "window.h"

Window::Window(WINDOW *win) {
    getmaxyx(win, height, width);
    this->win = win;
    left = width / 4;
    top = height / 4;

    colors_init();
}

void Window::print(std::string str, Color color) {
    attron(COLOR_PAIR(color.color));
    attron(color.attr);
    printw(str.c_str());
    attroff(COLOR_PAIR(color.color));
    attroff(color.attr);
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

void Window::putc(char c, Color color) {
    attron(COLOR_PAIR(color.color));
    attron(color.attr);
    addch(c);
    attroff(COLOR_PAIR(color.color));
    attroff(color.attr);
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

void Window::putcxy(char c, Color color, int x, int y) {
    move(y, x);
    putc(c, color);
}
