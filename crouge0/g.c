#include "g.h"

G new_g() {
    G g = malloc(sizeof(struct G));

    g->wmap = load_wmap();
    g->gmap = load_global_map();

    return g;
}

void free_g(G g) {
    free_wmap(g->wmap);
    free_map(g->gmap);
    free(g);
}
