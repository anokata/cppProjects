#pragma once
#ifndef __MAP_GEN__
#define __MAP_GEN__

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct Map {
    char *data;
    int width;
    int heigth;
} *Map;

int make_map(char *filename, int width, int heigth);

#endif
