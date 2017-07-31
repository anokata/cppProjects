#pragma once

#define DEBUG

#include "lib/ccurses.h"
#include "util.h"

typedef struct Tile {
    Color color;
    char c;
} Tile;

typedef struct TileMap {
    Tile *tiles;
    int width;
    int heigth;
} *TileMap;


TileMap make_tile_map(int width, int heigth);
TileMap load_tile_map(string filename);
void free_tile_map(TileMap map);

void print_tile_map(TileMap map);
string map_to2d(TileMap map);
Tile *tile_at(TileMap map, int x, int y);
