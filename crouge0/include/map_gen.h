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

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

typedef struct Map {
    char *data;
    int width;
    int heigth;
} *Map;

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct GlobalMapTile {
    char c;
    Color color;
} GlobalMapTile;

typedef struct WorldMapRegionDescriptor { //wmrd
    char c;
    Color color;
    string description;
} WorldMapRegionDescriptor;

typedef struct WorldMap {
    Map map;
    WorldMapRegionDescriptor *metadata;
} *WorldMap;

typedef struct G {
    WorldMap wmap;
    Point cursor;
    char key;
} *G;

G new_g();
void free_g(G g);

int out_map(char *filename, int width, int heigth);
Map load_map(string filename);
void free_map(Map map);
void print_map(Map map);

WorldMap load_wmap();
void free_wmap(WorldMap wmap);
void print_wmap(WorldMap wmap);



string load_global_map();

#endif
