#include <ncurses.h>
#include "app.h"
#include <utility>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "util.h"
//TODO  curses easy interface class: color manager? win, drawer
//window class
//

void print_by_line(std::string str, int x, int y) {
    auto lines = split(str, '\n');
    move(y, x);
    for (auto line : lines) {
        printw(line.c_str());
        y++;
        move(y, x);
    }
}

void App::key_handler(int key) {

}

void App::update() {
    //printw(sf.c_str());
    print_by_line(sf, window->width / 4, window->height / 4);
    /*
    printw(std::to_string(window->width).c_str());
    addch('\n');
    printw(std::to_string(window->height).c_str());
    printw(std::to_string(window->height / 2).c_str());

    move(29, 99);
    attron(COLOR_PAIR(1));
    addch('c' | A_BOLD);
    addch('.');
    attroff(COLOR_PAIR(1));
    */
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
