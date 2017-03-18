#include "dlist.h"

#define HASH_START_SIZE 100
//threshold for rehash
typedef struct Hash {
    uint32_t size;
    DList *table;
} Hash;

Hash *hash_new() {
    Hash *h = malloc(sizeof(*h));
    h->size = HASH_START_SIZE;
    DList *t = calloc(sizeof(DList), h->size);
    h->table = t;
    return h;
}

void hash_delete(Hash *h) {
    free(h->table);
    free(h);
}

#define DEBUG
#ifdef DEBUG
void test_create() {
    Hash *h = hash_new();
    hash_delete(h);
}

void test() {
    test_create();
}
//#include "_test.c"
int main() {
    test();
    return 0;
}
#endif
