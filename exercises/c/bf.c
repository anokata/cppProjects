#include <stdio.h>
#include <stdint.h>
//optarg

#define BF_MEMORY_SIZE 30000
typedef struct Machine {
    uint8_t *dp; // Data pointer; and data;
    char *ip; // Instruction pointer and code;
    // input output loops
    uint8_t *input;
    uint8_t *output;
} Machine;


int main(int argc, char** argv) {
    printf("Brainfuck interpreter v 0.0 (q)\n");
    return 0;
}
