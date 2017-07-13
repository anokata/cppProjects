#pragma once

#include <vector>
#include "window.h"


class Snake {
    std::vector<Point> segments;
    int max_x;
    int max_y;
    int get_next_x();
    int get_next_y();
    Direction opposite(Direction direction);

public:
    Snake(int max_x, int max_y) {
        segments.push_back(Point(1, 1));
        segments.push_back(Point(1, 2));
        segments.push_back(Point(1, 3));
        segments.push_back(Point(2, 3));
        this->max_x = max_x;
        this->max_y = max_y;
    }

    int getx() {
        return segments[0].first;
    }

    int gety() {
        return segments[0].second;
    }
    
    Color color = color::bred;
    bool is_growth = false;
    char head_char = 'o';
    char body_char = 's';
    Direction direction = Direction::Right;

    void draw(Window *window);
    void move();
    void growth();
    void self_bounce();
    void turn_back();
};
