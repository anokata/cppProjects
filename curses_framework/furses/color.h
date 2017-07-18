#pragma once
#ifndef __COLOR__
#define __COLOR__
#include <ncurses.h>

struct Color {
    int color;
    int attr;
};

namespace color {
    extern int red;
    extern int green;
    extern int blue;
    extern int yellow;
    extern int white;
    extern Color bgreen;
    extern Color ngreen;
    extern Color nred;
    extern Color bred;
    extern Color nwhite;
    extern Color bwhite;
    extern Color nblue;
    extern Color bblue;
}

void colors_init();
#endif
