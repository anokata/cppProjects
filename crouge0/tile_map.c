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

void copy_map2tiles(TileMap map, char *line, int len) {
    for (int i = 0; i < len; i++) {
        map->tiles[i].c = line[i];
    }
}

TileMap load_tile_map(string filename) {
    TileMap map = 0;
    FILE *file = fopen(filename, "r");
    int width = 0;
    int heigth = 0;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    width = fget_int_line(file);
    heigth = fget_int_line(file);
    DEBUG_PRINT("Loading tile map with w:%d h:%d\n", width, heigth);

    map = make_tile_map(width, heigth);

    read = getline(&line, &len, file);
    copy_map2tiles(map, line, read - 1);
    print_tile_map(map);

    if (line)
        free(line);
    fclose(file);
    return map;
}

void _copy_loc2glob(TileMap gmap, TileMap lmap, int offset) {
    for (int i = 0; i < lmap->heigth; i++) {
        memcpy(gmap->tiles + offset + i * gmap->width, 
               lmap->tiles + i * lmap->width, lmap->width * sizeof(struct Tile));
    }
}

TileMap load_global_tmap() {
    TileMap global_map;
    int local_width = 2;
    int local_height = 2;
    int local_map_width = 6;
    int local_map_height = 3;
    global_map = make_tile_map(local_width * local_map_width, local_height * local_map_height);
    string mapname_format = "maps/map_%i_%i";
    char mapname[100];
    int block_height = local_map_width * local_width * local_map_height;

    for (int i = 1; i <= local_height; i++) {
        for (int j = 1; j <= local_width; j++) {
            sprintf(mapname, mapname_format, i, j);
            printf("name: %s\n", mapname);
			TileMap lmap = load_tile_map(mapname);
            _copy_loc2glob(global_map, lmap, 
                    local_map_width * (j - 1) + (i - 1) * block_height);
			free_tile_map(lmap);
        }
    }
    
    return global_map;
}
