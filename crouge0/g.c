#include "g.h"

G new_g() {
    return malloc(sizeof(struct G));
}

void free_g(G g) {
    // free_wmap(g->wmap) ...
    free(g);
}
