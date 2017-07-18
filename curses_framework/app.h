#pragma once
#ifndef __APP__
#define __APP__
#include <utility>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <map>
#include <utility>
#include "furses/curses_app.h"
#include "furses/curses_wrapper.h"
#include "furses/state.h"
#include "furses/menu.h"
#include "furses/util.h"

typedef std::pair<int, int> Key;

class App : public CursesApp { 
    virtual int update();
    virtual void init();
    virtual void finalize();
    virtual int key_handler(int key);

    State state;
    Menu menu;
    int menu_update();
    int menu_key();
    int key;

    public:
        App();
};
#endif
