#pragma once
#ifndef __MAP_GEN__
#define __MAP_GEN__

#define _GNU_SOURCE

#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"

typedef struct Map {
    char *data;
    int width;
    int heigth;
} *Map;

typedef struct Point {
    int x;
    int y;
} Point;

int out_map(char *filename, int width, int heigth);

#endif
