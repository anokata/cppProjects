#include "world_map.h"

string world_map_filename = "world.map";

#define META 6
Color get_color_for_tile(WorldMap wmap, int x, int y) {
    char tile_char = map_char_at(wmap->map, x, y);
    for (int i = 0; i < META; i++) {
        if (wmap->metadata[i].c == tile_char) {
            return wmap->metadata[i].color;
        }
    }
    return cd_blue;
}

// DUBLICATE
Map load_wmap_file(string filename) {
    Map map = 0;
    FILE *file = fopen(filename, "r");
    int width = 0;
    int heigth = 0;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    width = fget_int_line(file);
    heigth = fget_int_line(file);
    map = make_map(width, heigth);

    for (int y = 0; y < heigth; y++) {
        read = getline(&line, &len, file);
        memcpy(map->data + y * width, line, read - 1); // -1 \n at end of line
    }

    if (line)
        free(line);
    fclose(file);
    return map;
}

WorldMap load_wmap() {
    Map map = load_wmap_file(world_map_filename);
    WorldMap wmap = malloc(sizeof(struct WorldMap));
    wmap->map = map;
    wmap->metadata = calloc(sizeof(WorldMapRegionDescriptor), META);
    for (int i = 0; i < META; i++) {
        wmap->metadata[i].color = cd_red;
    }
        wmap->metadata[0].c = ' ';
        wmap->metadata[0].description = "space";
        wmap->metadata[1].c = '%';
        wmap->metadata[1].description = "plains";
        wmap->metadata[1].color = cd_green;
        wmap->metadata[2].c = '^';
        wmap->metadata[2].description = "mountains";
        wmap->metadata[2].color = cd_white;
        wmap->metadata[3].c = '-';
        wmap->metadata[3].description = "swamp";
        wmap->metadata[3].color = cn_blue;
        wmap->metadata[4].c = '*';
        wmap->metadata[4].description = "forest";
        wmap->metadata[5].c = '.';
        wmap->metadata[5].description = "desert";
        wmap->metadata[5].color = cn_yellow;
    return wmap;
}

void free_wmap(WorldMap wmap) {
    free_map(wmap->map);
    free(wmap->metadata);
    free(wmap);
}

void print_wmap(WorldMap wmap) {
    Map map = wmap->map;
    for (int y = 0; y < map->heigth; y++) {
        for (int x = 0; x < map->width; x++) {
            Color color = get_color_for_tile(wmap, x, y);
            cc_putxy(map_char_at(map, x, y), color, x, y);
        }
    }
}
