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
index_t hash_addi(Hash *h, uint32_t x);
index_t hash_adds(Hash *h, char *s);
index_t hash_add(Hash *h, void *data);
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

index_t hash_addi(Hash *h, uint32_t x) {
    index_t idx = hashi(h, x);
    HashNode *node = malloc(sizeof(x));
    node->data = (void*)(uint64_t)x;
    node->key = idx;
    list_push(&h->table[idx], node);
    return idx;
}

void* hash_get(Hash *h, index_t key) {
    if (h->table[key].length == 0) {
        printf("Not\n");
        return 0;
    }
    list_print(&h->table[key]);

    return hash_list_find(&h->table[key], key);
}

#define DEBUG
#ifdef DEBUG
#include <stdio.h>
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
    index_t k = hash_addi(h, 123);
    printf("key %d\n", k);
    void *d =hash_get(h, k);
    hash_get(h, 121);
    printf("%ld\n", (long)d);
    hash_delete(h);
}
void test_collisions() {

}

void test() {
    test_create();
    test_add();
    test_collisions();
    //test_hashs();
    getc(stdin);
}
//#include "_test.c"
int main() {
    test();
    return 0;
}
#endif
