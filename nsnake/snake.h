#pragma once

#include <vector>
#include "window.h"

typedef std::pair<int, int> Point;

class Snake {
    std::vector<Point> segments;

public:
    Snake() {
        segments.push_back(Point(1, 1));
    }
    //color
    char head_char = 'o';
    //body_char

    void draw(Window *window); // TODO implement
};
