#include "tile_map.h"

int main() {
    TileMap m = make_tile_map(2, 3);
    print_tile_map(m);
    free_tile_map(m);
}
