#pragma once
#ifndef __COLOR__
#define __COLOR__
#include <ncurses.h>

static const int BACKGROUND = -1; // COLOR_BLACK

typedef struct Color {
    int color;
    int attr;
} Color;

typedef int color_index;

#define _cn_red 1
#define _cn_green 2
#define _cn_black 3
#define _cn_white 4
#define _cn_yellow 5
#define _cn_blue 12
static const struct Color cn_red = {_cn_red, A_NORMAL};
static const struct Color cb_red = {_cn_red, A_BOLD};
static const struct Color cd_red = {_cn_red, A_DIM};
static const struct Color cn_blue = {_cn_blue, A_NORMAL};
static const struct Color cb_blue = {_cn_blue, A_BOLD};
static const struct Color cd_blue = {_cn_blue, A_DIM};
static const struct Color cn_yellow = {_cn_yellow, A_NORMAL};
static const struct Color cb_yellow = {_cn_yellow, A_BOLD};
static const struct Color cd_yellow = {_cn_yellow, A_DIM};
static const struct Color cn_white = {_cn_white, A_NORMAL};
static const struct Color cb_white = {_cn_white, A_BOLD};
static const struct Color cd_white = {_cn_white, A_DIM};

void cc_init_colors();

#endif
