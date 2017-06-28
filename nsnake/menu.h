#pragma once
#ifndef __MENU__
#define __MENU__
#include <functional>
#include <vector>
#include <cstdint>

typedef std::function<void(void)> Runner;
typedef std::pair<std::string, Runner> MenuItem;

class Menu {

    std::vector<MenuItem> items;
    uint16_t index = 0;

    public:
        Menu() {}
        void add(std::string item, Runner fun);
        void select();
        void next();
        void back();

};

#endif
