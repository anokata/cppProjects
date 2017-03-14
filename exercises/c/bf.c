#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//optarg

#define BF_MEMORY_SIZE 30000
typedef struct Machine {
    uint8_t *data; 
    uint8_t dp; // Data pointer;
    char *code; 
    char ip; // Instruction pointer 
    // input output loops
    uint8_t *input;
    uint8_t *output;
} Machine;

Machine* make_machine() {
    Machine* m = malloc(sizeof(Machine));
    m->data = malloc(BF_MEMORY_SIZE);
    m->dp = 0;
    m->ip = 0;

    return m;
}

void down_machine(Machine* m) {
    free(m->data);
    free(m);
}

int main(int argc, char** argv) {
    printf("Brainfuck interpreter v 0.0 (q)\n");
    Machine* m = make_machine();
    printf("> Machine maked.\n");
    down_machine(m);
    printf("Quited.");
    return 0;
}
