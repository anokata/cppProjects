#include "map_gen.h"

Map make_map(int width, int heigth) {
    Map map = malloc(sizeof(struct Map));
    char *data = calloc(width * heigth, 1);
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

string map_to2d(Map map) {
    int nwidth = map->width + 1;
    string map2d = malloc(1 + map->heigth * nwidth);
    memset(map2d, 0, map->heigth * nwidth);

    for (int i=0; i < map->heigth; i++) {
        for (int j=0; j < map->width; j++) {
            map2d[i * nwidth + j] = map->data[i * map->width + j];
        }
        if (i < map->heigth - 1)
            map2d[(i + 1) * nwidth - 1] = '\n';
    }
    return map2d;
}

int get_map_size(Map map) {
    return map->width * map->heigth;
}

void print_map(Map map) {
    string m2;
    m2 = map_to2d(map);
    printf("%s\n", m2);
    free(m2);
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

    fwrite(map->data, get_map_size(map), 1, file);
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

    read = getline(&line, &len, file);
    memcpy(map->data, line, read);
    /* print_map(map); */

    if (line)
        free(line);
    fclose(file);
    return map;
}

// ToDo
void _copy_loc2glob(string gmap, Map lmap, int offset) {
    for (int i = 0; i < lmap->heigth; i++) {
        memcpy(gmap + offset + i * lmap->width, 
               lmap->data + i * lmap->width, lmap->width);
    }
}

string load_global_map() {
// make normal Map
    Map global_map;
    int local_width = 2;
    int local_height = 1;
    int local_map_width = 6;
    int local_map_height = 3;
    int local_size = local_map_width * local_map_height;
    int size = local_width * local_size * local_height;
    string gmap = malloc(size);
    memset(gmap, '-', size);
    string mapname_format = "maps/map_%i_%i";
    char mapname[100];
    int left = 0;

    for (int i = 1; i <= local_height; i++) {
        for (int j = 1; j <= local_width; j++) {
            sprintf(mapname, mapname_format, i, j);
            printf("name: %s\n", mapname);
			Map lmap = load_map(mapname);
            left = (j - 1) * local_map_width;
            string m2 = map_to2d(lmap);
            // COpy by line to glob
            _copy_loc2glob(gmap, lmap, local_size * ( i + j - 2));
            // string g2 = map_to2d(gmap); and print
            printf("%s\n", m2);
            free(m2);
			free_map(lmap);
        }
    }
    
    return gmap;
}
