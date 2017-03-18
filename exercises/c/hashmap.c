#include "dlist.h"

#define HASH_START_SIZE 100
//threshold for rehash
typedef struct Hash {
    size_t size;
    DList *table;
} Hash;

typedef struct HashNode {
    uint32_t key;
    void *data;
} HashNode;

typedef uint32_t index_t;
void hash_delete(Hash *h);
Hash *hash_new();
index_t hash_addi(Hash *h, uint32_t key, uint32_t x);
index_t hash_adds(Hash *h, uint32_t key, char *s);
index_t hash_add(Hash *h, uint32_t key, void *data);
void* hash_get(Hash *h, index_t key);
void *hash_list_find(DList *list, index_t key);

void *hash_list_find(DList *list, index_t key) {
    DListNode *cur = list->head;
    HashNode hnode = *(HashNode*)cur->data;
    while (cur && hnode.key != key) {
        cur = cur->next;
        hnode = *(HashNode*)cur->data;
    }
    if (!cur) {
        return 0;
    }
    return hnode.data;
}

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

index_t hashv(void *data, size_t size) {
    return 0; // stumb
}
index_t hashi(Hash *h, uint32_t x) {
    return (x*0xABCD) % h->size;
}
index_t hashstr(Hash *h, char* s) {
    return '0';
}

index_t hash_addi(Hash *h, uint32_t key, uint32_t x) {
    index_t idx = hashi(h, key);
    HashNode *node = malloc(sizeof(x));
    node->data = (void*)(uint64_t)x;
    node->key = key;
    list_push(&h->table[idx], node);
    return idx;
}

void* hash_get(Hash *h, index_t key) {
    index_t idx = hashi(h, key);
    if (h->table[idx].length == 0) {
        printf("Not\n");
        return 0;
    }
    list_print(&h->table[idx]);
    return hash_list_find(&h->table[idx], key);
}

#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#include <math.h>
#include <time.h>
void test_create() {
    Hash *h = hash_new();
    hash_delete(h);
}
void test_hashs() {
    Hash *h = hash_new();
    for (int i = 0; i < 100; i++) {
        printf("hashi: %d \n", hashi(h, i));
    }
    hash_delete(h);
}
void test_add() {
    Hash *h = hash_new();
    index_t k = hash_addi(h, 1, 123);
    printf("key %d\n", k);
    void *d = hash_get(h, 1);
    printf("%ld\n", (long)d);
    hash_delete(h);
}
void test_collisions() {
    Hash *h = hash_new();
    for (int i = 0; i < 10; i++) {
        hash_addi(h, i, 3215);
        void *d = hash_get(h, i);
        printf("add %d get val %ld", i, (long)d);
        if (3215 == (long)d)
            printf(" OK\n");
        else
            printf(" NOT!!\n");
    }

    hash_addi(h, 241, 999);
    void *d = hash_get(h, 241);
    printf("add %d get val %ld\n", 241, (long)d);
    hash_addi(h, 741, 888);
    d = hash_get(h, 741);
    printf("add %d get val %ld\n", 741, (long)d);
    hash_delete(h);
}
uint32_t test_find_collision() {
    Hash *h = hash_new();
    srand(time(0));
    index_t x = rand() % 1000;
    index_t y = rand() % 1000;
    index_t k1 = hash_addi(h, x, 1);
    index_t k2 = hash_addi(h, y, 2);
    while (k1 != k2) {
        x = rand() % 1000;
        y = rand() % 1000;
        k1 = hash_addi(h, x, 1);
        k2 = hash_addi(h, y, 2);
    }
    printf("\n%d %d %d\n", x, y, k1);
    hash_delete(h);
    // 241 741
}

void test() {
    test_create();
    test_add();
    test_collisions();
    test_find_collision();
    //test_hashs();
    getc(stdin);
}
//#include "_test.c"
int main() {
    test();
    return 0;
}
#endif
