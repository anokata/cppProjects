#include "window.h"

Window::Window(WINDOW *win) {
    getmaxyx(win, height, width);
    this->win = win;
}
