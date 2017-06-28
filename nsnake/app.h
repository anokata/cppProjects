#pragma once
#include "curses_app.h"
#include <map>
#include <utility>
#include "snake.h"
#include "object.h"
#include "state.h"
#include "menu.h"

typedef std::pair<int, int> Key;

class App : public CursesApp { 
    virtual void update();
    virtual void init();
    virtual void finalize();
    virtual void key_handler(int key);
    virtual void collide();
    static const int DIM_X = 20;
    static const int DIM_Y = 10;

    std::map<Key, char> field; 
    std::string sf = "";
    Snake snake = Snake(DIM_X, DIM_Y);
    std::map<Key, PObject> objects;
    State state;
    Menu menu;
    int key;

    /* snake app specific */
    void add_bonus();
    void step();
    void play_update();
    void play_key();
    void menu_update();
    void menu_key();

    public:
    App();
};
