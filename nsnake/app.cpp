#include <ncurses.h>
#include "app.h"
#include <utility>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "util.h"
#include "snake.h"
//TODO  curses easy interface class: color manager? win, drawer
//window class
//
//bonuses

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
    char k = key;
    switch (key) {
        case 'j': snake.direction = Direction::Down;
        break;
        case 'k': snake.direction = Direction::Up;
        break;
        case 'h': snake.direction = Direction::Left;
        break;
        case 'l': snake.direction = Direction::Right;
        break;
    }
}

void App::update() {
    print_by_line(sf, window->width / 4, window->height / 4); // TODO?
    snake.move();
    snake.draw(window);
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
