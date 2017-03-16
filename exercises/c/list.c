#include <stdlib.h>
#include <stdio.h>

typedef struct List {
    struct List* next;
    void* data;
} List;

typedef void* (*List_map_func)(void*);

List* list_add(List** list, void* data) {
    List* new_elem;
    new_elem = malloc(sizeof(*new_elem));
    new_elem->data = data;
    new_elem->next = 0;

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

// safe(func to save one elem(fd))
// map list
#define DEBUG

#ifdef DEBUG
int main() {
    List *l; 
    int a = 812;
    char s[] = "a;d;d'z'";
    l = list_add(0, &a);
    l = list_add(&l, &s);
    printf("%d\n", *(int*)l->next->data);
    list_add(&l, &s);
    printf("%s\n", (char*)l->data);
    list_print(l);
    list_p(l);
    return 0;
}
#endif
