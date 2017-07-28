#include "map_gen.h"

string world_map_filename = "world.map";
char map_char_at(Map map, int x, int y);
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

WorldMap load_wmap() {
    Map map = load_map(world_map_filename);
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

Map make_map(int width, int heigth) {
    Map map = malloc(sizeof(struct Map));
    char *data = calloc(width, heigth);
    map->data = data;
    map->width = width;
    map->heigth = heigth;
    for (int i=0; i < heigth; i++) {
        for (int j=0; j < width; j++) {
            data[i * width + j] = ' ';
        }
    }
    return map;
}

void free_map(Map map) {
    free(map->data);
    free(map);
}

static const char *map_chars = ".o";
int map_chars_count = 0;

char rand_char() {
    return map_chars[rand() % map_chars_count];
}

char map_char_at(Map map, int x, int y) {
    return map->data[y * map->width + x];
}

int map_neighbours(Map map, Point p) {
    int n = 0;

    return n;
}

void gen_map_step(Map map) {

}

Map gen_map(int width, int heigth) {
    time_t t;
    srand((unsigned) time(&t));
    map_chars_count = strlen(map_chars);

    Map map = make_map(width, heigth);

    for (int i=0; i < heigth; i++) {
        for (int j=0; j < width; j++) {
            map->data[i * width + j] = rand_char();
        }
    }
    return map;
}

int get_map_size(Map map) {
    return map->width * map->heigth;
}

void print_map(Map map) {
    for (int i=0; i < map->heigth; i++) {
        for (int j=0; j < map->width; j++) {
            putchar(map->data[i * map->width + j]);
        }
        putchar('\n');
    }
}

// to viewable with newlines, from viewable/editable in vi
// mode for open view map in editor in tmp file, edit, save and convert to map.

int out_map(char *filename, int width, int heigth) {
    Map map = gen_map(width, heigth);
    FILE *file = fopen(filename, "w");

    char *buf = malloc(100);
    sprintf(buf, "%d\n%d\n", map->width, map->heigth);
    fwrite(buf, strlen(buf), 1, file);
    free(buf);

    fwrite(map->data, strlen(map->data), 1, file);
    fclose(file);

    DEBUG_PRINT("Map:\n");
    print_map(map);
    DEBUG_PRINT("Saved to %s\n", filename);
    free_map(map);
    return 0;
}

int fget_int_line(FILE *file) {
    int value = 0;
    char * line = NULL;
    size_t len = 0;
    getline(&line, &len, file);
    sscanf(line, "%d", &value);
    if (line)
        free(line);
    return value;
}

Map load_map(string filename) {
    Map map = 0;
    FILE *file = fopen(filename, "r");
    int width = 0;
    int heigth = 0;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    width = fget_int_line(file);
    heigth = fget_int_line(file);
    DEBUG_PRINT("w:%d h:%d\n", width, heigth);

    map = make_map(width, heigth);

    for (int y = 0; y < heigth; y++) {
        read = getline(&line, &len, file);
        memcpy(map->data + y * width, line, read - 1); // -1 \n at end of line
    }
    /* print_map(map); */

    if (line)
        free(line);
    fclose(file);
    return map;
}

G new_g() {
    return malloc(sizeof(struct G));
}

void free_g(G g) {
    // free_wmap(g->wmap) ...
    free(g);
}
