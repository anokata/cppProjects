#pragma once

#include "map.h"

typedef struct G {
    WorldMap wmap;
    Point cursor;
    char key;
} *G;

G new_g();
void free_g(G g);
