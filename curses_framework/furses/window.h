#pragma once
#include <ncurses.h>
#include <string>
#include <map>
#include "color.h"

typedef enum Direction { Up, Down, Right, Left, UpLeft, UpRight, DownLeft, DownRight } Direction;
typedef std::pair<int, int> Point;
/* map poing(x, y) -> char */
typedef std::map<Point, char> CharMap;

class Window {
    public:
    int width;
    int height;
    WINDOW *win;
    int left;
    int top;

    Window(WINDOW *win);
    void print(std::string str, int color);
    void print(std::string str, Color color, int x, int y);
    void putc(char c, int color);
    void putc(char c, int color, int attr);
    void putcxy(char c, int color, int x, int y);
    /* colors */
    void print(std::string str, Color color);
    void putc(char c, Color color);
    void putcxy(char c, Color color, int x, int y);
};
