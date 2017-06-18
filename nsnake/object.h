#pragma once
#include "window.h"
#include <vector>

typedef enum Effect { GROW } Effect;

class Object {

    public:
        Object(int x, int y) : x(x), y(y) {
            frames.push_back('-');
            frames.push_back('+');
        }

        // Collision effect.
        Effect effect = Effect::GROW;
        int x;
        int y;
        char chr = 'G';

        std::vector<int> frames;
        int frame = 0;

        Color color = color::bgreen;
        void draw(Window *window);
};

typedef Object *PObject;
