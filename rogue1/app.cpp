#include "app.h"
// debug log window!

void App::bm_draw_border() {
    int h = 30;
    window->print("+----------------------------------+", color::nblue, 0, 0);
    window->print("+----------------------------------+", color::nblue, 0, h);
    for (int i = 1; i < h; i++) {
        window->print("|", color::nblue, 0, i);
        window->print("|", color::nblue, 35, i);
    }
}

void App::bm_draw() {
    bm_draw_border();
    for (auto cell : cm.dots) {
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
    switch (key) {
        case 'j': man.move(Direction::Down, cm.dots);
        break;
        case 'k': man.move(Direction::Up, cm.dots);
        break;
        case 'h': man.move(Direction::Left, cm.dots);
        break;
        case 'l': man.move(Direction::Right, cm.dots);
        break;
        case 'y': man.move(Direction::UpLeft, cm.dots);
        break;
        case 'u': man.move(Direction::UpRight, cm.dots);
        break;
        case 'b': man.move(Direction::DownLeft, cm.dots);
        break;
        case 'n': man.move(Direction::DownRight, cm.dots);
        break;
    }
    return 0;
}

int App::key_handler(int key) { 
    this->key = key;
    return state.handle("key");
}

int App::menu_key() {
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

int App::menu_update() {
    menu.draw(window);
    return 0;
}

int App::update() {
    return state.handle("step"); 
}

void App::init() {
    state.bind_event("menu", "step", std::bind(&App::menu_update, this));
    state.bind_event("menu", "key", std::bind(&App::menu_key, this));
    state.bind_event("exit", "key", [](){ return 1; });
    state.bind_event("bm", "step", std::bind(&App::bm_step, this));
    state.bind_event("bm", "key", std::bind(&App::bm_key, this));
    state.change("bm");

    menu.add("bm", [this](){ this->state.change("bm"); return 0; });
    menu.add("start", [this](){ this->state.change("play"); return 0; });
    menu.add("setup", [this](){ this->state.change("exit"); return 0; });
    menu.add("exit", [this](){ this->state.change("exit"); return 1; });

    this->cm = generate();
    objects.push_back(StaticObject(1, 2));
}

App::App() {
}

void App::finalize() {
}
