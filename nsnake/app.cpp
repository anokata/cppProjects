#include <ncurses.h>
#include "app.h"

void App::key_handler(int key) {

}

void App::update() {
    move(2, 1);
    attron(COLOR_PAIR(1));
    addch('c' | A_BOLD);
    addch('.');
    attroff(COLOR_PAIR(1));
}
