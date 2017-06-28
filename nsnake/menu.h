#pragma once
#ifndef __MENU__
#define __MENU__
#include <functional>
#include <vector>
#include <cstdint>
#include <ncurses.h>
#include "window.h"

typedef std::function<int(void)> Runner;
typedef std::pair<std::string, Runner> MenuItem;

class Menu {

    std::vector<MenuItem> items;
    uint16_t index = 0;

    public:
        Menu() {}
        void add(std::string item, Runner fun);
        int select();
        void next();
        void back();
        void draw(Window *window);

};

#endif
