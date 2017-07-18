#include "app.h"

int App::key_handler(int key) { 
    this->key = key;
    return state.handle("key");
}

int App::menu_key() {
    char k = key;
    switch (k) {
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
    return state.handle("step"); // TODO const or enum
}

void App::init() {
    state.bind_event("menu", "step", std::bind(&App::menu_update, this));
    state.bind_event("menu", "key", std::bind(&App::menu_key, this));
    state.bind_event("exit", "key", [](){ return 1; });
    state.change("menu");

    menu.add("start", [this](){ this->state.change("play"); return 0; });
    menu.add("setup", [this](){ this->state.change("exit"); return 0; });
    menu.add("exit", [this](){ this->state.change("exit"); return 1; });
}

App::App() {
}

void App::finalize() {
}
