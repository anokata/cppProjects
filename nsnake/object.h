#pragma once
#include "window.h"

typedef enum Effect { GROW } Effect;

class Object {

    public:
        Object(int x, int y) : x(x), y(y) {
        }

        // Collision effect.
        Effect effect = Effect::GROW;
        int x;
        int y;
        char chr = 'G';
        int color = Window::cl_red;
        void draw(Window *window);
};

typedef Object *PObject;
