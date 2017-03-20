#include "dlist.h"

#define HASH_START_SIZE 100
//threshold for rehash
typedef struct Hash {
    size_t size;
    DList *table;
    size_t count;
} Hash;

typedef union key_u {
    char *skey;
    uint32_t ikey;
} key_u;

typedef enum ekey_type {KEY_UINT32, KEY_STR} ekey_type;

typedef struct key_s {
    ekey_type key_type;
    key_u val;
} key_s;

typedef struct HashNode {
    key_s key;
    void *data;
} HashNode;

typedef uint32_t index_t;
typedef void* (*Hash_map_func)(key_s key, void* value);
void hash_delete(Hash *h);
Hash *hash_new();
index_t hash_addi(Hash *h, uint32_t key, void* x);
index_t hash_add(Hash *h, key_s key, void *data);
void *hash_get(Hash *h, key_s key);
void *hash_list_find(DList *list, key_s key);
void hash_mapv(Hash *h, List_map_func);
void hash_map(Hash *h, Hash_map_func);
void hash_remove(Hash *h, index_t key);
index_t hash(Hash *h, key_s k);
index_t hashi(Hash *h, uint32_t x);
index_t hashs(Hash *h, char* x);
index_t hashstr(Hash *h, char* s);

key_s keystr(char *str);
key_s keyint(uint32_t x);

key_s keystr(char *str) {
    key_s key;
    key.key_type = KEY_STR;
    key.val.skey = str;
    return key;
}

key_s keyint(uint32_t x) {
    key_s key;
    key.key_type = KEY_UINT32;
    key.val.ikey = x;
    return key;
}

int keycmpi(key_s k, uint32_t x) {
    return (k.val.ikey == x);
}

int keycmps(key_s k, char* str) {
    return strcmp(k.val.skey, str);
}

int keycmp(key_s k, key_s m) {
    if (k.key_type == m.key_type) {
        switch (k.key_type) {
            case (KEY_UINT32):
                printf("keycmp %d %d\n", k.val.ikey, m.val.ikey);
                return (k.val.ikey == m.val.ikey);
            case (KEY_STR):
                return strcmp(k.val.skey, m.val.skey);
            default:
                return -1;
        };
    } else {
        return -1;
    }
}

void *hash_list_find(DList *list, key_s key) {
    DListNode *cur = list->head;
    HashNode hnode = *(HashNode*)cur->data;
    while (cur && !keycmp(key, hnode.key)) {
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
    for (size_t i = 0; i < h->size; i++) {
        list_init(&h->table[i]);
    }
    h->count = 0;
    return h;
}

void hash_delete(Hash *h) {
    for (size_t i = 0; i < h->size; i++) {
        //printf("free list #%ld\n", i);
        list_delete_onlynodes(&h->table[i]);
    }
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
    index_t idx = 0;
    for (int i = 0; i < strlen(s); i++) {
        idx += s[i];
    }
    idx %= h->size;
    return idx; 
}

index_t hash(Hash *h, key_s k) {
    switch (k.key_type) {
        case KEY_UINT32:
            return hashi(h, k.val.ikey);
        case KEY_STR:
            return hashstr(h, k.val.skey);
    };
}

index_t hash_addi(Hash *h, uint32_t key, void* x) {
    return hash_add(h, keyint(key), x);
}

index_t hash_add(Hash *h, key_s key, void *data) {
    HashNode *node = malloc(sizeof(*node));
    node->data = data;
    index_t idx = hash(h, key);
    node->key = key;
    list_push(&h->table[idx], node);
    h->count += 1;
    return idx;

}

void* hash_get(Hash *h, key_s key) {
    index_t idx = hash(h, key);
    if (h->table[idx].length == 0) {
        printf("Not\n");
        return 0;
    }
    list_print(&h->table[idx]);
    return hash_list_find(&h->table[idx], key);
}

void hash_remove(Hash *h, index_t key) {
    index_t idx = hashi(h, key);
//TODO
}

void hash_mapv(Hash *h, List_map_func fun) {
    // maybe store save keys in list?
    for (size_t i = 0; i < h->size; i++) {
        list_map(&h->table[i], fun);
    }
}

void hash_map(Hash *h, Hash_map_func fun) {
    for (size_t i = 0; i < h->size; i++) {
        DListNode *cur = h->table[i].head;
        while (cur) {
            HashNode *hnode = cur->data;
            void *result = fun(hnode->key, hnode->data);
            hnode->data = result;
            cur = cur->next;
        }
    }
}

void* hash_print_func(void* data) {
    HashNode *hnode = data;
    key_s k = hnode->key;
    switch (k.key_type) {
        case KEY_UINT32:
            printf("key %d : val %ld\n", hnode->key.val.ikey, (long)hnode->data);
            break;
        case KEY_STR:
            printf("key [%s] : val %ld\n", hnode->key.val.skey, (long)hnode->data);
            break;
    }
    return data;
}

void hash_print_values(Hash *h) {
    hash_mapv(h, hash_print_func);
}

// TODO: delete at key
// count items
// rehash(calc fullness (count/size))
// string keys
// map over keys/vals. for free too
// non typed values
// Cli. Lib
// save/load separator data, text format DSV with | delimeter
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
    printf("str hash %d \n", hashstr(h, "a"));
    hash_delete(h);
}
void test_add() {
    Hash *h = hash_new();
    index_t k = hash_addi(h, 1, (void*)123);
    printf("key %d\n", k);
    void *d = hash_get(h, keyint(1));
    printf("get %ld\n", (long)d);
    hash_delete(h);
}
void test_collisions() {
    Hash *h = hash_new();
    for (int i = 0; i < 10; i++) {
        hash_addi(h, i, (void*)3215);
        void *d = hash_get(h, keyint(i));
        printf("add %d get val %ld", i, (long)d);
        if (3215 == (long)d)
            printf(" OK\n");
        else
            printf(" NOT!!\n");
    }

    hash_addi(h, 241, (void*)999);
    void *d = hash_get(h, keyint(241));
    printf("add %d get val %ld\n", 241, (long)d);
    hash_addi(h, 741, (void*)888);
    d = hash_get(h, keyint(741));
    printf("add %d get val %ld\n", 741, (long)d);
    hash_delete(h);
}
uint32_t test_find_collision() {
    Hash *h = hash_new();
    srand(time(0));
    index_t x = rand() % 1000;
    index_t y = rand() % 1000;
    index_t k1 = hash_addi(h, x, (void*)1);
    index_t k2 = hash_addi(h, y, (void*)2);
    while (k1 != k2) {
        x = rand() % 1000;
        y = rand() % 1000;
        k1 = hash_addi(h, x, (void*)1);
        k2 = hash_addi(h, y, (void*)2);
    }
    printf("\n%d %d %d\n", x, y, k1);
    hash_delete(h);
    // 241 741
}
void test_print() {
    Hash *h = hash_new();
    hash_addi(h, 1, (void*)113);
    hash_addi(h, 1, (void*)114);
    hash_addi(h, 2, (void*)212);
    hash_addi(h, 3, (void*)34);
    hash_print_values(h);
    hash_delete(h);
}
void test_stringkey() {
    Hash *h = hash_new();
    hash_add(h, keystr("key1"), (void*)12);
    hash_print_values(h);
    hash_delete(h);
}

void test() {
    test_create();
    test_add();
    test_collisions();
    test_find_collision();
    test_print();
    test_stringkey();
    //test_hashs();
    getc(stdin);
}
//#include "_test.c"
int main() {
    test();
    return 0;
}
#endif
