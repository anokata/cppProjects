#include "color.h"
using namespace color;
int color::red = 1;
int color::green = 2;
int color::blue = 3;
int color::yellow = 4;
int color::white = 5;
Color color::bgreen = {color::green, A_BOLD};
Color color::ngreen = {color::green, A_NORMAL};
Color color::nred = {color::red, A_NORMAL};
Color color::bred = {color::red, A_BOLD};
Color color::nwhite = {color::white, A_NORMAL};
Color color::bwhite = {color::white, A_BOLD};

static const int BACKGROUND = -1; // COLOR_BLACK

void colors_init() {
    init_pair (color::red, COLOR_RED, BACKGROUND);
    init_pair (color::blue, COLOR_BLUE, BACKGROUND);
    init_pair (color::yellow, COLOR_BLUE, BACKGROUND);
    init_pair (color::green, COLOR_GREEN, BACKGROUND);
    /* init_pair (color::white, COLOR_WHITE, COLOR_BLACK); */
    init_pair (color::white, COLOR_WHITE, -1);
    /* use_default_colors(); */
}
