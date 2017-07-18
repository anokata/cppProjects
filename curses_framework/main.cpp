#include <iostream>
#include <ncurses.h>
#include "furses/curses_wrapper.h"
#include "furses/curses_app.h"
#include "app.h"

int main() {
    CursesWrapper::load(new App());
    CursesWrapper::start();
    return 0;
}

