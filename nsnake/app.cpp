#include <ncurses.h>
#include "app.h"
#include <utility>
//TODO  curses easy interface class: color manager? win, drawer
//window class

void App::key_handler(int key) {

}

void App::update() {
    move(0, 0);
    printw("abc");

    move(2, 1);
    attron(COLOR_PAIR(1));
    addch('c' | A_BOLD);
    addch('.');
    attroff(COLOR_PAIR(1));
}

App::App() {
    for (int x=0; x < 10; x++) {
        for (int y=0; y < 10; y++) {
            Key key (x, y);
            field.insert(std::make_pair(key, cfield));

        }
    }
}
