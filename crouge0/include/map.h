#pragma once
#include "lib/ccurses.h"
#include "util.h"

typedef struct Map {
    char *data; // TODO Tile
    int width;
    int heigth;
} *Map;

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct WorldMapRegionDescriptor { //wmrd
    char c;
    Color color;
    string description;
} WorldMapRegionDescriptor;

typedef struct WorldMap {
    Map map;
    WorldMapRegionDescriptor *metadata;
} *WorldMap;


typedef struct GlobalMapTile {
    char c;
    Color color;
} GlobalMapTile;

typedef struct Tile {
    Color color;
    char c;
} Tile;
