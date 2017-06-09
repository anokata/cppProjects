#pragma once

#include <vector>
#include "window.h"

typedef std::pair<int, int> Point;
typedef enum Direction {Up, Down, Right, Left} Direction;

class Snake {
    std::vector<Point> segments;

public:
    Snake() {
        segments.push_back(Point(1, 1));
        segments.push_back(Point(1, 2));
        segments.push_back(Point(1, 3));
        segments.push_back(Point(2, 3));
    }

    int getx() {
        return segments[0].first;
    }

    int gety() {
        return segments[0].second;
    }
    
    int color = Window::cl_red;
    bool is_growth = false;
    char head_char = 'o';
    char body_char = 's';
    Direction direction = Direction::Right;

    void draw(Window *window);
    void move();
    void growth();
};
