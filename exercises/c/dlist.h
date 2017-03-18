#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
// Double linked list

typedef void (*free_node_fnc)(void*);
typedef void* (*List_map_func)(void*);
typedef char* (*data_to_str_fnc)(void*);

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
// TODO
// find

