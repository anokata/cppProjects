#pragma once
#ifndef __SLOW_MSG__
#define __SLOW_MSG__

#include "window.h"

class SlowMsg {
    std::string msg;
    int frame = 0;

public:
    SlowMsg(std::string str) {
        this->msg = str;
    }

    bool draw(Window *window);
};

#endif

