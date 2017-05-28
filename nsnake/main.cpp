#include <iostream>
#include <ncurses.h>
#include "curses_wrapper.h"
#include "curses_app.h"
#include "app.h"

int main() {
    CursesWrapper::load(new App());
    CursesWrapper::start();
    return 0;
}

