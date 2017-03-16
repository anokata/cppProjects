#include <stdlib.h>
#include <stdio.h>

typedef struct List {
    struct List* next;
    void* data;
} List;

typedef void* (*List_map_func)(void*);

List* list_add(List** list, void* data);

List* list_new(void* data) {
    List* new_elem; 
    new_elem = malloc(sizeof(*new_elem));
    new_elem->data = data;
    new_elem->next = 0;
    return new_elem;
}

void list_push(List** list, void* data) {
    List* new_elem = list_new(data);

    if (*list == 0) {
        (*list) = new_elem;
        return;
    }
    while ((*list)->next) {
        *list = (*list)->next;
    }
    (*list)->next = new_elem;
}

List* list_add(List** list, void* data) {
    List* new_elem = list_new(data);

    if (list == 0) {
        return new_elem;
    } else {
        new_elem->next = *list;
        *list = new_elem;
        return new_elem;
    }
}

void list_map(List* list, List_map_func f) {
    while (list) {
        list->data = f(list->data);
        list = list->next;
    }
}

void* list_print_func(void* data) {
    printf("data: %p int(%d) long(%ld) ", data, *(int*)data, *(long*)data);
    printf("str(%s) \n", (char*)data);
    return data;
}

void list_print(List *list) {
    int i = 1;
    while (list) {
        printf("Item[%d] ", i++);
        printf("next: %p  ", list->next);
        printf("data: %p int(%d) long(%ld) ", list->data, *(int*)list->data, *(long*)list->data);
        printf("str(%s) \n", (char*)list->data);
        list = list->next;
    }
    printf("\n");
}

void list_p(List* list) {
    list_map(list, list_print_func);
}


// save(func to save one elem(fd))
// push pop append remove take head tail slice reduce
// delete delete_map
// save/load serialization
#define DEBUG

#ifdef DEBUG
#include <string.h>
int main() {
    List *l; 
    int a = 812;
    char s[] = "Linked List.";
    l = list_add(0, &a);
    l = list_add(&l, &s);
    printf("%d\n", *(int*)l->next->data);
    list_add(&l, &s);
    for (int i = 0; i < strlen(s); i++) {
        //list_add(&l, s+i);
    }
    printf("%s\n", (char*)l->data);
    list_print(l);
    list_p(l);

    int b = 3; int c = 4;
    l = 0;
    list_push(l, &a);
    list_push(l, &b);
    list_push(l, &c);
    list_p(l);
    return 0;
}
#endif
