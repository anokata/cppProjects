#include "map_gen.h"

Map make_map(int width, int heigth) {
    Map map = malloc(sizeof(struct Map));
    char *data = calloc(width, heigth);
    map->data = data;
    map->width = width;
    map->heigth = heigth;
    for (int i=0; i < width; i++) {
        for (int j=0; j < width; j++) {
            data[i*width + j] = '.';
        }
    }
    return map;
}

void free_map(Map map) {
    free(map->data);
    free(map);
}

Map gen_map(int width, int heigth) {
    Map map = make_map(width, heigth);

    return map;
}

int get_map_size(Map map) {
    return map->width * map->heigth;
}

void print_map(Map map) {
    for (int i=0; i < map->width; i++) {
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
    // TODO write width heigth
    fwrite(map, strlen(map->data), sizeof(char), file);
    fclose(file);
    printf("Map:\n");
    print_map(map);
    printf("Saved to %s\n", filename);
    free_map(map);
    return 0;
}

int main() {
    out_map("/tmp/test.map", 10, 15);
}
