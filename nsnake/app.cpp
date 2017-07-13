#include <ncurses.h>
#include <utility>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include "app.h"
#include "util.h"
#include "snake.h"
#include "level_gen.h"
//TODO  curses easy interface class, extract core
//bonuses
//scores top
//menu
//quest, step move, labirint
//x. flowers
//x. lighting
// barriers
// levels
// end level
// - score, eathed, length, level, total
// debug log window!
// extract curses lib
// 'slow' typing messages
// global timer, time intervals
/* https://stackoverflow.com/questions/19022320/implementing-timer-with-timeout-handler-in-c */
// border corners
// bomberman
// dynamic background color changing random text dropdown

void App::bm_draw_border() {
    window->print("+----------------------------------+", color::nblue, 0, 0);
    window->print("+----------------------------------+", color::nblue, 0, 20);
    for (int i = 1; i < 20; i++) {
        window->print("|", color::nblue, 0, i);
        window->print("|", color::nblue, 35, i);
    }
}

void App::bm_draw() {
    bm_draw_border();
    for (auto cell : cm) {
        window->putcxy(cell.second, color::nblue, cell.first.first, cell.first.second);
    }
    man.draw(window);
    man.draw_info(window);
}

int App::bm_step() {
    bm_draw();
    return 0;
}

int App::bm_key() {
    char k = key;
    switch (key) {
        case 'j': man.move(Direction::Down);
        break;
        case 'k': man.move(Direction::Up);
        break;
        case 'h': man.move(Direction::Left);
        break;
        case 'l': man.move(Direction::Right);
        break;
    }
    return 0;
}

void print_by_line(std::string str, int x, int y) {
    auto lines = split(str, '\n');
    move(y, x);
    for (auto line : lines) {
        printw(line.c_str());
        y++;
        move(y, x);
    }
}

int App::key_handler(int key) { //TODO state depended
    this->key = key;
    return state.handle("key");
}

int App::menu_key() {
    char k = key;
    switch (key) {
        case 'j': menu.next();
        break;
        case 'k': menu.back();
        break;
        case '\n': return menu.select();
        break;
    }
    return 0;
}

int App::play_key() {
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
    return 0;
}

void App::draw_ui() {
    int cx = window->left;
    int cy = window->top;
    std::stringstream fmt;
    fmt << "|--- " << "Score: (" << eated << ")" << " Level: " << 0 << " ---|";
    window->print(fmt.str().c_str(), color::nwhite, cx, cy - 1);
    window->print("/", color::nwhite, cx + window->width, cy + 3);
    window->print("+", color::nwhite, cx - 1, cy - 1);
    msg1.draw(window);
}

int App::play_update() {
    print_by_line(sf, window->width / 4, window->height / 4); // TODO?
    collide();
    snake.move();
    snake.draw(window);
    for (auto i : objects) {
        PObject obj = i.second;
        obj->draw(window);
    }
    draw_ui();
    return 0;
}

int App::menu_update() {
    menu.draw(window);
    draw_ui();
    return 0;
}

int App::update() {
    return state.handle("step"); // TODO const or enum
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
                    eated++;
                    snake.growth();
                    objects.erase(i.first);
                    delete obj;
                    break;
                    
                case Effect::STOP:
                    snake.turn_back();
                    break;
            }
        }
    }
    snake.self_bounce();
}

int App::add_bonus() {
    int rx = std::rand() % DIM_X;
    int ry = std::rand() % DIM_Y;
    objects[Point(rx, ry)] = new Object(rx, ry);
    return 0;
}


int App::add_wall() {
    int rx = std::rand() % DIM_X;
    int ry = std::rand() % DIM_Y;
    objects[Point(rx, ry)] = new Object(rx, ry);
    objects[Point(rx, ry)]->effect = Effect::STOP;
    objects[Point(rx, ry)]->frames.clear();
    objects[Point(rx, ry)]->frames.push_back('#');
    return 0;
}

void App::init() {
    state.bind_event("play", "step", std::bind(&App::play_update, this));
    state.bind_event("play", "eat", std::bind(&App::add_bonus, this));
    state.bind_event("menu", "step", std::bind(&App::menu_update, this));
    state.bind_event("menu", "key", std::bind(&App::menu_key, this));
    state.bind_event("play", "key", std::bind(&App::play_key, this));
    state.bind_event("exit", "key", [](){ return 1; });
    state.bind_event("bm", "step", std::bind(&App::bm_step, this));
    state.bind_event("bm", "key", std::bind(&App::bm_key, this));
    state.change("bm");

    menu.add("bm", [this](){ this->state.change("bomberman"); return 0; });
    menu.add("start", [this](){ this->state.change("play"); return 0; });
    menu.add("setup", [this](){ this->state.change("exit"); return 0; });
    menu.add("exit", [this](){ this->state.change("exit"); return 1; });
    menu.add("stars", [this](){ this->state.change("stars"); return 1; });

    this->cm = generate();

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
    for (int i = 0; i < 20; i++) {
        add_bonus();
        add_wall();
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
