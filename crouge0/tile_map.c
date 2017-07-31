#include "tile_map.h"

TileMap make_tile_map(int width, int heigth) {
    TileMap map = malloc(sizeof(struct TileMap));
    Tile *tiles = calloc(width * heigth, sizeof(struct Tile));
    map->tiles = tiles;
    map->width = width;
    map->heigth = heigth;
    for (int i=0; i < heigth; i++) {
        for (int j=0; j < width; j++) {
            tiles[i * width + j].c = '.';
        }
    }
    return map;
}

void free_tile_map(TileMap map) {
    free(map->tiles);
    free(map);
}

Tile *tile_at(TileMap map, int x, int y) {
    Tile *tile = map->tiles + y * map->width + x;
    return tile;
}

string tilemap_to2d(TileMap map) {
    int nwidth = map->width + 1;
    string map2d = malloc(1 + map->heigth * nwidth);
    memset(map2d, 0, map->heigth * nwidth);
memset(map2d, '-', map->heigth * nwidth - 1);

    for (int i=0; i < map->heigth; i++) {
        for (int j=0; j < map->width; j++) {
            map2d[i * nwidth + j] = tile_at(map, j, i)->c;
        }
        if (i < map->heigth - 1)
            map2d[(i + 1) * nwidth - 1] = '\n';
    }
    return map2d;
}

void print_tile_map(TileMap map) {
    string m2;
    m2 = tilemap_to2d(map);
    DEBUG_PRINT("w:%d h:%d\n", map->width, map->heigth);
    printf("%s\n", m2);
    free(m2);
}
