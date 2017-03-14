#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//optarg

#define BF_MEMORY_SIZE 30000
typedef struct Machine {
    uint8_t *data; 
    uint8_t dp; // Data pointer
    char *code; 
    uint8_t ip; // Instruction pointer 
    // loops
    uint8_t ii; // Output index
    uint8_t *input;
    uint8_t oi; // Output index
    uint8_t *output;
} Machine;

Machine* make_machine(char* code, uint8_t* input) {
    Machine* m = malloc(sizeof(Machine));
    m->data = malloc(BF_MEMORY_SIZE);
    m->dp = 0;
    m->ip = 0;
    m->oi = 0;
    m->ii = 0;
    m->code = code;
    m->output = malloc(100);
    m->input = input;

    return m;
}

void down_machine(Machine* m) {
    free(m->output);
    free(m->data);
    free(m);
}

void print_machine(Machine* m) {
    printf("%s\n", m->code);
    for (int i = 0; i < m->ip; i++) {
        printf(" ");
    }
    printf("^\n");
    printf("IP: %d  DP: %d \n", m->ip, m->dp);
    printf("II: %d  OI: %d \n", m->ii, m->oi);
    printf("OUT: '%s'\n", m->output);
    printf("Data:\n");
    const int maxv = 64;
    for (int base = 0; base < maxv; base += 16) {
        printf("0x%04X:    ", base);
        for (int i = 0; i < 16; i++) {
            printf("%02X ", m->data[base + i]);
        }
        for (int i = 0; i < 16; i++) {
            printf("%c", m->data[base + i]);
        }
        printf("\n");
    }
}

void machine_cmd_dpinc(Machine* m) {
    m->dp++;
}

void machine_cmd_dpdec(Machine* m) {
    m->dp--;
}

void machine_cmd_datainc(Machine* m) {
    m->data[m->dp]++;
}

void machine_cmd_datadec(Machine* m) {
    m->data[m->dp]--;
}

void machine_cmd_out(Machine* m) {
    m->output[m->oi++] = m->data[m->dp];
}

void machine_cmd_in(Machine* m) {
    m->data[m->dp] = m->input[m->ii++];
}

void test_m() {
    uint8_t input[] = "some";
    char code[] = ",+[-.,+]";
    Machine* m = make_machine(code, input);
    printf("> Machine maked.\n");
    machine_cmd_dpinc(m);
    machine_cmd_datainc(m);
    machine_cmd_dpinc(m);
    machine_cmd_datadec(m);
    machine_cmd_out(m);
    machine_cmd_dpdec(m);
    machine_cmd_out(m);
    machine_cmd_dpinc(m);
    machine_cmd_out(m);
    machine_cmd_in(m);
    machine_cmd_out(m);
    machine_cmd_dpinc(m);
    machine_cmd_in(m);
    machine_cmd_out(m);
    print_machine(m);
    down_machine(m);
}

int main(int argc, char** argv) {
    printf("Brainfuck interpreter v 0.0 (q)\n");
    test_m();
    printf("Quited.");
    return 0;
}
