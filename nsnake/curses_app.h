#pragma once

// abstract
class CursesApp { 
    
public:
    virtual void update() = 0;
    virtual void key_handler(int key) = 0;
};
