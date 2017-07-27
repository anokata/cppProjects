#pragma once
#ifndef __MAP_GEN__
#define __MAP_GEN__

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "lib/ccurses.h"
#include "util.h"

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
Map load_map(string filename);

typedef struct WorldMapRegionDescriptor { //wmrd
    char c;
    Color color;
    string description;
} WorldMapRegionDescriptor;

/* WorldMapRegionDescriptor world_map_metadata[] = { */
/*     {' ', .description="space"}, */
/*     {'%', .description="plains"}, */
/*     {'-', .description="swarm"}, */
/*     {'^', .description="mountains"}, */
/*     {'*', .description="forest"}, */
/*     {'.', .description="desert"} */
/* }; */


#endif
