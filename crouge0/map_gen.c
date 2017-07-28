#include "map_gen.h"

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

    Map map = make_map(width + 1, heigth);

    for (int i=0; i < heigth; i++) {
        for (int j=0; j < width; j++) {
            map->data[i * (width + 1) + j] = rand_char();
        }
		map->data[i * (width + 1)] = '\n';
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
        /* putchar('\n'); */
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

	// TODO by lines
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

string load_global_map() {
    int local_width = 2;
    int local_height = 1;
    int local_map_width = 20;
    int local_map_height = 20;
    string gmap = malloc(local_width 
            * local_map_width 
            * local_height 
            * local_map_height); // Free
    string mapname_format = "maps/map_%i_%i";
    char mapname[100];
    int left = 0;

    for (int i = 1; i <= local_height; i++) {
        for (int j = 1; j <= local_width; j++) {
            sprintf(mapname, mapname_format, i, j);
            printf("name: %s\n", mapname);
			Map lmap = load_map(mapname);
            left = (j - 1) * local_map_width;
            /* memcpy(gmap + left, line, read - 1); */
            /* printf("->%s\n", lmap->data); */
			free_map(lmap);
        }
    }

    return gmap;
}
