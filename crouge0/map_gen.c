#include "map_gen.h"

char *gen_map(int width, int heigth) {
    char *map = calloc(width, heigth);

    return map;
}

void print_map(Map map) {

}

// to viewable with newlines, from viewable/editable in vi

int make_map(char *filename, int width, int heigth) {
    char *map = gen_map(width, heigth);
    FILE *file = fopen(filename, "w");
    fwrite(map, strlen(map), sizeof(char), file);
    fclose(file);
    printf("Map:\n%s\nSaved to %s\n", map, filename);
    free(map);
    return 0;
}

int main() {
    make_map("/tmp/test.map", 10, 15);
}
