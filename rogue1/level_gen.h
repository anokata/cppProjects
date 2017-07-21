#pragma once
#ifndef __LEVEL_GEN__
#define __LEVEL_GEN__

#include <ctime>
#include "furses/window.h"

template <class T> class Map {
    public:
        int width;
        int height;
        T dots;
};

typedef Map<CharMap> CharsMap;

CharsMap generate();

#endif

