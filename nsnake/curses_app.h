#pragma once

// abstract
class CursesApp { 
protected:
    char cfield = '.';
    
public:
    // inject window or in construct
    virtual void update() = 0;
    virtual void key_handler(int key) = 0;
};
