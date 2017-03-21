#include "dlist.h"
void free_node_stumb(void* ptr) {
    //printf("* Free at %p\n", ptr);
    //free(ptr);
}

char* data_to_str_stumb(void* data) { // ALLOC
    char* str = malloc(sizeof(uint32_t) + 1);
    sprintf(str, "%d", *((uint32_t*)data));
    return str;
}

void list_init(DList *list) {
    list->length = 0;
    list->head = 0;
    list->tail = 0;
    list->free_fnc = free_node_stumb;
    list->tostr_fnc = data_to_str_stumb;
    list->data_size = sizeof(uint32_t);
}

DList* list_new() {
    DList* list = malloc(sizeof(*list));
    list_init(list);
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
    if (next)
        next->back = back;
    if (back)
        back->next = next;
    if (ln == list->head)
        list->head = ln->next;
    if (ln == list->tail)
        list->tail = ln->back;
    list->free_fnc(ln->data);
    free(ln);
    return next;
}

void list_delete_onlynodes(DList* list) {
    DListNode* cur = list->head;
    while(cur) {
        DListNode* next = cur->next;
        list->free_fnc(cur->data);
        free(cur);
        cur = next;
    }
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

int list_erase_at(DList *list, uint32_t index) {
    if (list->length < index || index < 0) return -1;
    DListNode *cur = list->head;
    while(index--) {
        cur = cur->next;
    }
    list_delete_node(list, cur);
    list->length--;
    return 0;
}

#define DELIMITER |
char *list_get_dsvstr(DList *list) {

}

int list_saveDSVfile(DList* list, char* fn) {

}

// save/load separator data, text format DSV with | delimeter
// save(func to save one elem(fd))
// push pop append remove take head tail slice reduce
// delete delete_map
// get erase insert
// save/load serialization
// make text format with sep
//#define DEBUG
#ifdef DEBUG
#include "dlist_test.c"
#endif
