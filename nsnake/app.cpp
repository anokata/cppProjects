#include <ncurses.h>
#include "app.h"
#include <utility>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include "util.h"
#include "snake.h"
//TODO  curses easy interface class, extract core
//bonuses
//state machine
//scores top
//menu
//quest, step move, labirint
//x. flowers
//x. lighting
// - score, eathed, length, level, total
/* State: one instance - state, global for app
 *
 * */

void print_by_line(std::string str, int x, int y) {
    auto lines = split(str, '\n');
    move(y, x);
    for (auto line : lines) {
        printw(line.c_str());
        y++;
        move(y, x);
    }
}

void App::key_handler(int key) { //TODO state depended
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

void App::play_update() {
    print_by_line(sf, window->width / 4, window->height / 4); // TODO?
    collide();
    snake.move();
    snake.draw(window);
    for (auto i : objects) {
        PObject obj = i.second;
        obj->draw(window);
    }
}

void App::menu_update() {

}

void App::update() {
    state.handle("step"); // TODO const or enum
}

void App::step() {
}

void App::collide() {
    for (auto i : objects) {
        Point p = i.first;
        if (p.first == snake.getx() && p.second == snake.gety()) {
            PObject obj = i.second;
            if (obj == NULL) continue;
            switch (obj->effect) {
                case Effect::GROW:
                    state.handle("eat");
                    snake.growth();
                    objects.erase(i.first);
                    delete obj;
                    break;
            }
        }
    }
    snake.self_bounce();
}

void App::add_bonus() {
    int rx = std::rand() % DIM_X;
    int ry = std::rand() % DIM_Y;
    objects[Point(rx, ry)] = new Object(rx, ry);
}

void App::init() {
    state.bind_event("play", "step", std::bind(&App::play_update, this));
    state.bind_event("play", "eat", std::bind(&App::add_bonus, this));
    state.bind_event("menu", "step", std::bind(&App::menu_update, this));
    state.change("menu");

    for (int x=0; x < DIM_Y; x++) {
        for (int y=0; y < DIM_X; y++) {
            Key key (x, y);
            field.insert(std::make_pair(key, cfield));
            sf += cfield;
        }
        sf += '\n';
    }
    /* Random bonuses */
    std::srand(unsigned(std::time(0)));
    for (int i = 0; i < 2; i++) {
        add_bonus();
    }
    objects[Point(1, 1)] = new Object(1, 1);
}

App::App() {
}

void App::finalize() {
    for (auto obj : objects) {
        delete obj.second;
    }
}
