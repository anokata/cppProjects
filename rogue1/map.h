#pragma once
#ifndef __MAP_
#define __MAP__

typedef int coord;

class MapObject {
    protected:
        coord x;
        coord y;

    public:
        std::string symbol = " ";

        MapObject(coord x, coord y) : x(x), y(y) {}
        coord getx() { return x; }
        coord gety() { return y; }
        virtual void draw(Window *window) = 0;
};

// https://en.wikipedia.org/wiki/C%2B%2B11#Object_construction_improvement
class StaticObject {

    public:
        std::string symbol = "S";
        void draw(Window *window);
        //using MapObject::MapObject;
        StaticObject(coord x, coord y) {
        }
};


#endif
