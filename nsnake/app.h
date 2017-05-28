#pragma once
#include "curses_app.h"

class App : public CursesApp { 
    virtual void update();
    virtual void key_handler(int key);
};
