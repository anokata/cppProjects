#pragma once
#include "window.h"

// abstract
class CursesApp { 
protected:
    char cfield = '.';
    
public:
    // inject window or in construct
    Window *window;
    virtual void init() = 0;
    virtual void finalize() = 0;
    virtual void update() = 0;
    virtual void key_handler(int key) = 0;
};
