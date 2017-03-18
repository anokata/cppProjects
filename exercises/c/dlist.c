#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
// Double linked list
// make header

typedef void (*free_node_fnc)(void*);
typedef void* (*List_map_func)(void*);
typedef char* (*data_to_str_fnc)(void*);

void free_node_stumb(void* ptr) {
    printf("* Free at %p\n", ptr);
    //free(ptr);
}

char* data_to_str_stumb(void* data) { // ALLOC
    char* str = malloc(sizeof(uint32_t) + 1);
    sprintf(str, "%d", *((uint32_t*)data));
    return str;
}

typedef struct DListNode { 
    struct DListNode* next;
    struct DListNode* back;
    void* data;
} DListNode;

typedef struct DList {
    DListNode* head;
    DListNode* tail;
    uint32_t length;
    uint32_t data_size;
    free_node_fnc free_fnc;
    data_to_str_fnc tostr_fnc;
} DList;

DListNode* list_newnode(void* data);
DList* list_new();
void list_p(DList* list);
void list_print(DList *list);
void list_map(DList* list, List_map_func f);
void* list_print_func(void* data);
void* list_pop(DList* list);
int list_push(DList* list, void* data);
int list_add(DList* list, void* data);
int list_remove(DList* list);
void list_delete(DList* list);


DList* list_new() {
    DList* list = malloc(sizeof(*list));
    list->length = 0;
    list->head = 0;
    list->tail = 0;
    list->free_fnc = free_node_stumb;
    list->tostr_fnc = data_to_str_stumb;
    list->data_size = sizeof(uint32_t);
    return list;
}

DListNode* list_newnode(void* data) {
    DListNode* new_elem; 
    new_elem = malloc(sizeof(*new_elem));
    new_elem->data = data;
    new_elem->next = 0;
    new_elem->back = 0;
    return new_elem;
}

int list_push(DList* list, void* data) {
    DListNode* ln = list->head;
    DListNode* new_elem = list_newnode(data);
    list->length++;
    if (ln == 0) {
        list->head = new_elem;
        list->tail = new_elem;
        return 0;
    }
    list->tail->next = new_elem;
    new_elem->back = list->tail;
    list->tail = new_elem;
    return 0;
}

int list_remove(DList* list) {
    if (list->length == 0) {
        return 0;
    }
    DListNode* old_head = list->head;
    list->head = list->head->next;
    if (list->head)
        list->head->back = 0;
    list->free_fnc(old_head->data);
    free(old_head);
    list->length--;
    if (list->length == 0) {
        list->tail = 0;
    }
    return 0;
}

void* list_pop(DList* list) {
    DListNode* lst = list->head;
    if (list->length == 0) {
        return 0;
    }
    if (list->length == 1) {
        void* data = list->head->data;
        list->free_fnc(list->head->data);
        free(list->head);
        list->head = 0;
        list->tail = 0;
        list->length--;
        return data;
    } else {
        list->length--;
        lst = list->tail->back;
        void* data = lst->next->data;
        list->free_fnc(lst->next->data);
        free(lst->next);
        lst->next = 0;
        list->tail = lst;
        return data;
    }
}

int list_add(DList* list, void* data) {
    DListNode* new_elem = list_newnode(data);
    list->length++;

    if (list->head == 0) {
        list->head = new_elem;
        list->tail = new_elem;
        return 0;
    } else {
        new_elem->next = list->head;
        list->head->back = new_elem;
        list->head = new_elem;
        return 0;
    }
}

void list_map(DList* list, List_map_func f) {
    DListNode *ln = list->head;
    while (ln) {
        ln->data = f(ln->data);
        ln = ln->next;
    }
}

void* list_print_func(void* data) {
    printf("data: %p int(%d) long(%ld) ", data, *(int*)data, *(long*)data);
    printf("str(%s) \n", (char*)data);
    return data;
}

void list_print(DList *list) {
    int i = 1;
    DListNode *ln = list->head;
    while (ln) {
        printf("Item[%d] ", i++);
        printf("next: %p  ", ln->next);
        printf("data: %p int(%d) long(%ld) ", ln->data, *(int*)ln->data, *(long*)ln->data);
        printf("str(%s) \n", (char*)ln->data);
        ln = ln->next;
    }
    printf("\n");
}

void list_p(DList* list) {
    list_map(list, list_print_func);
}

DListNode* list_delete_node(DList* list, DListNode* ln) {
    DListNode* next = ln->next;
    DListNode* back = ln->back;
    next->back = back;
    back->next = next;
    list->free_fnc(ln->data);
    free(ln);
    return next;
}

void list_delete(DList* list) {
    DListNode* cur = list->head;
    while(cur) {
        DListNode* next = cur->next;
        list->free_fnc(cur->data);
        free(cur);
        cur = next;
    }
    list->length = 0;
    list->head = 0;
    list->tail = 0;
    free(list);
}

const static uint32_t LIST_TAG = 'D' + ('L' << 8) + ('S' << 16) + ('T' << 24);

int list_save2file(DList* list, char* fn) {
	FILE *fd = fopen(fn, "w");
	if (!fd) {
		perror("open");
		return -1;
	}
    // TODO first serialize to memory, after write once
	size_t bytes = fwrite(&LIST_TAG, sizeof(LIST_TAG), 1, fd);
    DListNode* cur = list->head;
    bytes += fwrite(&list->length, sizeof(uint32_t), 1, fd);
    bytes += fwrite(&list->data_size, sizeof(uint32_t), 1, fd);
    while (cur) {
        // TODO convert data to serialized
        bytes += fwrite(cur->data, list->data_size, 1, fd);
        cur = cur->next;
    }
	printf("* writed %ld items\n", bytes);
	fclose(fd);
	return 0;
}

DList *list_loadfile(char* fn) {
    FILE *fd = fopen(fn, "r");
    if (!fd) {
        perror("open for load");
        return 0;
    }
    DList *list = list_new();
    // check tag
    uint32_t tag;
    size_t readed = fread(&tag, sizeof(tag), 1, fd);
    if (!readed) {
        perror("not read");
        return 0;
    }
    if (tag != LIST_TAG) {
        perror("Tag not is LIST");
        return 0;
    }
    uint32_t length;
    uint32_t size;
    void *data;
    fread(&length, sizeof(list->length), 1, fd);
    fread(&size, sizeof(list->data_size), 1, fd);
    list->data_size = size;
    for (size_t i = 0; i < length; i++) {
        data = malloc(size);
        fread(data, size, 1, fd);
        list_push(list, data);
    }

    return list;
}

void *list_free_data(void *data) {
    free(data);
    return 0;
}

// save(func to save one elem(fd))
// push pop append remove take head tail slice reduce
// delete delete_map
// get erase insert
// save/load serialization
#define DEBUG

#ifdef DEBUG
#include <string.h>
void test_create() {
    printf("* TEST create \n");
    DList *l; 
    l = list_new();
    l->head = 0;
    list_delete(l);
}
void test_create_and_remove() {
    printf("* TEST create and remove one \n");
    DList *l; 
    l = list_new();
    list_remove(l);
    list_delete(l);
}
void test_create_and_delete() {
    printf("* TEST create and delete all\n");
    DList *l; 
    l = list_new();
    list_delete(l);
}
void test_add() {
    printf("* TEST ADD\n");
    DList *l = list_new();
    int a = 5;
    int b = 6;
    list_add(l, &a);
    list_add(l, &b);
    printf("Len:%d\tH:%p\tT:%p\n", l->length, l->head, l->tail);
    printf("Head next %p\t back %p\t data %p(%d)\n", l->head->next, l->head->back, l->head->data, *(int*)l->head->data);
    list_print(l);
    list_remove(l);
    list_print(l);
    list_add(l, &b);
    list_print(l);
    list_delete(l);
}
void test_push() {
    printf("* TEST PUSH\n");
    DList *l = list_new();
    int a = 5;
    int b = 6;
    list_push(l, &a);
    list_push(l, &b);
    printf("Len:%d\tH:%p\tT:%p\n", l->length, l->head, l->tail);
    printf("Head next %p\t back %p\t data %p(%d)\n", l->head->next, l->head->back, l->head->data, *(int*)l->head->data);
    list_print(l);
    list_remove(l);
    list_print(l);
    list_push(l, &b);
    list_print(l);
    list_delete(l);
}
void test_pop() {
    printf("* TEST POP\n");
    DList *l = list_new();
    int a = 5;
    int b = 6;
    list_push(l, &a);
    list_push(l, &b);
    printf("Len:%d\tH:%p\tT:%p\n", l->length, l->head, l->tail);
    printf("Head next %p\t back %p\t data %p(%d)\n", l->head->next, l->head->back, l->head->data, *(int*)l->head->data);
    list_print(l);
    int x = *(int*)list_pop(l);
    printf("poped: %d\n", x);
    list_print(l);
    list_push(l, &b);
    list_print(l);
    x = *(int*)list_pop(l);
    printf("poped: %d\n", x);
    x = *(int*)list_pop(l);
    printf("poped: %d\n", x);
    list_print(l);
    list_push(l, &b);
    list_add(l, &a);
    list_print(l);
    list_delete(l);
}
void test_backs() {
    printf("* TEST BACKS\n");
    DList *l = list_new();
    int a = 5;
    int b = 6;
    list_push(l, &a);
    list_push(l, &b);
    DListNode* c = l->tail;
    while (c) {
        printf("self %p\tnext %p\t back %p\t data %p(%d)\n", c, c->next, c->back, c->data, *(int*)c->data);
        c = c->back;
    }
    list_print(l);
    list_remove(l);
    list_print(l);
    a = 8;
    list_push(l, &a);
    list_print(l);
    c = l->tail;
    while (c) {
        printf("self %p\tnext %p\t back %p\t data %p(%d)\n", c, c->next, c->back, c->data, *(int*)c->data);
        c = c->back;
    }
    list_pop(l);
    list_push(l, &a);
    c = l->tail;
    while (c) {
        printf("self %p\tnext %p\t back %p\t data %p(%d)\n", c, c->next, c->back, c->data, *(int*)c->data);
        c = c->back;
    }
    list_delete(l);
}
void test_all() {
    DList *l; 
    int a = 812;
    char s[] = "Linked List.";
    l = list_new();
    list_add(l, &a);
    list_add(l, &s);
    printf("%d\n", *(int*)l->head->next->data);
    list_add(l, &s);
    printf("%s\n", (char*)l->head->data);
    list_print(l);
    list_p(l);
    int b = 3; int c = 4;
    list_delete(l);
    l = list_new();
    list_push(l, &a);
    list_push(l, &b);
    list_push(l, &c);
    list_p(l);
    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int d = 5;
    list_delete(l);
    l = list_new();
    list_push(l, &x1);
    list_push(l, &x2);
    list_push(l, &x3);
    list_add(l, &c);
    list_add(l, &d);
    printf("pop = %d len(%d)\n", *(int*)list_pop(l), l->length);
    printf("pop = %d len(%d)\n", *(int*)list_pop(l), l->length);
    printf("pop = %d len(%d)\n", *(int*)list_pop(l), l->length);
    printf("h = %d\n", *(int*)l->head->data);
    printf("t = %d\n", *(int*)l->tail->data);
    printf("xh = %p\n", (int*)l->head);
    printf("xt = %p\n", (int*)l->tail);
    printf("pop = %d len(%d)\n", *(int*)list_pop(l), l->length);
    printf("h = %p\n", (int*)l->head);
    printf("t = %p\n", (int*)l->tail);
    printf("\n");
    list_p(l);
    list_delete(l);
    l = list_new();
    list_push(l, &x1);
    list_push(l, &x2);
    list_push(l, &x3);
    list_add(l, &c);
    list_add(l, &d);
    list_remove(l);
    printf("pop = %d len(%d)\n", *(int*)list_pop(l), l->length);
    list_remove(l);
    list_p(l);
    list_delete(l);
    list_p(l);
}
void test_leaks() {
    DList* l = list_new();
    int a = 1;
    int b = 2;
    list_push(l, &a);
    list_push(l, &a);
    list_push(l, &a);
    list_pop(l);
    list_pop(l);
    list_pop(l);
    list_add(l, &a);
    list_add(l, &a);
    list_add(l, &a);
    list_pop(l);
    list_pop(l);
    list_pop(l);
    list_delete(l);
    l = list_new();
    list_add(l, &a);
    list_add(l, &b);
    list_add(l, &a);
    printf("3 rem\n");
    list_remove(l);
    list_remove(l);
    list_remove(l);
    list_push(l, &a);
    list_push(l, &a);
    list_push(l, &a);
    list_remove(l);
    list_remove(l);
    list_remove(l);
    list_delete(l);
}
void test_save() {
    int a = 1; int b = 2;
    DList* l = list_new();
    list_push(l, &a);
    list_add(l, &b);
    list_save2file(l, "testsavelist");
    list_delete(l);
}

void test_load() {
    DList *l = list_loadfile("testsavelist");
    printf("loaded %d items\n", l->length);
    list_p(l);
    list_map(l, list_free_data);
    list_delete(l);
}


void test() {
    test_create();
    test_create_and_delete();
    test_create_and_remove();
    test_add();
    test_push();
    test_backs();
    test_pop();
    test_all();
    test_leaks();
    test_save();
    test_load();
    return;
}

int main() {
    test();
    //test_leaks();
    return 0;
}
#endif
