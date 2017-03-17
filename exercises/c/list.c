#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct ListNode { // Node
    struct ListNode* next;
    void* data;
} ListNode;

//on delete func. store on main list struct.
typedef struct List {
    ListNode* head;
    ListNode* tail;
    uint32_t length;
} List;

typedef void* (*List_map_func)(void*);
ListNode* list_newnode(void* data);
List* list_new();
int list_push(List* list, void* data);
int list_add(List* list, void* data);
void* list_pop(List* list);

List* list_new() {
    List* list = malloc(sizeof(*list));
    list->length = 0;
    list->head = 0;
    list->tail = 0;
    return list;
}

ListNode* list_newnode(void* data) {
    ListNode* new_elem; 
    new_elem = malloc(sizeof(*new_elem));
    new_elem->data = data;
    new_elem->next = 0;
    return new_elem;
}

int list_push(List* list, void* data) {
    ListNode* ln = list->head;
    ListNode* new_elem = list_newnode(data);
    list->length++;
    if (ln == 0) {
        list->head = new_elem;
        return 0;
    }
    while (ln->next) {
        ln = ln->next;
    }
    ln->next = new_elem;
    list->tail = new_elem;
    return 0;
}

void* list_pop(List* list) {
    ListNode* lst = list->head;
    if (list->length == 0) {
        return 0;
    }
    if (list->length == 1) {
        //free
        void* data = lst->data;
        list->head = 0;
        list->tail = 0;
        list->length--;
        return data;
    } else {
        list->length--;
        while (lst->next->next != 0) {
            lst = lst->next;
        }
        void* data = lst->next->data;
        //free
        lst->next = 0;
        list->tail = lst;
        return data;
    }
}

int list_add(List* list, void* data) {
    ListNode* new_elem = list_newnode(data);
    list->length++;

    if (list->head == 0) {
        list->head = new_elem;
        list->tail = new_elem;
        return 0;
    } else {
        new_elem->next = list->head;
        list->head = new_elem;
        return 0;
    }
}

void list_map(List* list, List_map_func f) {
    ListNode *ln = list->head;
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

void list_print(List *list) {
    int i = 1;
    ListNode *ln = list->head;
    while (ln) {
        printf("Item[%d] ", i++);
        printf("next: %p  ", ln->next);
        printf("data: %p int(%d) long(%ld) ", ln->data, *(int*)ln->data, *(long*)ln->data);
        printf("str(%s) \n", (char*)ln->data);
        ln = ln->next;
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
    l = list_new();
    list_add(l, &a);
    list_add(l, &s);
    printf("%d\n", *(int*)l->head->next->data);
    list_add(l, &s);
    printf("%s\n", (char*)l->head->data);
    list_print(l);
    list_p(l);

    int b = 3; int c = 4;
    l = list_new();
    list_push(l, &a);
    list_push(l, &b);
    list_push(l, &c);
    list_p(l);
    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int d = 5;
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
    return 0;
}
#endif
