#pragma once
#include "curses_app.h"
#include <map>
#include <utility>
#include "snake.h"

typedef std::pair<int, int> Key;

class App : public CursesApp { 
    virtual void update();
    virtual void init();
    virtual void key_handler(int key);

    std::map<Key, char> field; 
    std::string sf = "";
    Snake snake;

    public:
    App();
};
