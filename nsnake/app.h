#pragma once
#include "curses_app.h"
#include <map>
#include <utility>
#include <map>
#include "snake.h"
#include "object.h"

typedef std::pair<int, int> Key;

class App : public CursesApp { 
    virtual void update();
    virtual void init();
    virtual void finalize();
    virtual void key_handler(int key);
    virtual void collide();

    std::map<Key, char> field; 
    std::string sf = "";
    Snake snake;
    std::map<Key, PObject> objects;

    public:
    App();
};
