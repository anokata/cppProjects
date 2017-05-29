#include <ncurses.h>
#include "app.h"
#include <utility>
//TODO  curses easy interface class: color manager? win, drawer
//window class
//

void print_by_line(std::string) {

    //printw(.c_str());
}

void App::key_handler(int key) {

}

void App::update() {
    //move(window->height / 2, window->width / 2);
    move (0, 0);
    printw(sf.c_str());
    printw(std::to_string(window->width).c_str());
    addch('\n');
    printw(std::to_string(window->height).c_str());
    printw(std::to_string(window->height / 2).c_str());

    move(29, 99);
    attron(COLOR_PAIR(1));
    addch('c' | A_BOLD);
    addch('.');
    attroff(COLOR_PAIR(1));
}

void App::init() {
    for (int x=0; x < (window->height - 1) / 2 ; x++) {
        for (int y=0; y < (window->width) / 2; y++) {
            Key key (x, y);
            field.insert(std::make_pair(key, cfield));
            sf += cfield;
        }
        sf += '\n';
    }
}

App::App() {
}
