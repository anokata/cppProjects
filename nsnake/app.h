#pragma once
#include "curses_app.h"
#include <map>
#include <utility>
#include "snake.h"
#include "object.h"
#include "state.h"
#include "menu.h"
#include "slow_msg.h"
#include "man.h"
#include "level_gen.h"

typedef std::pair<int, int> Key;

class App : public CursesApp { 
    virtual int update();
    virtual void init();
    virtual void finalize();
    virtual int key_handler(int key);
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
    int add_bonus();
    int add_wall();
    void step();
    int play_update();
    int play_key();
    int menu_update();
    int menu_key();
    void draw_ui();
    /* bm spec */
    void bm_draw();
    void bm_draw_border();
    int bm_step();
    int bm_key();
    Man man = Man(2, 3);
    /* stats */
    int eated = 0;

    SlowMsg msg1 = SlowMsg("abc, def. Geh jkl!");
    CharsMap cm;

    public:
    App();
};
