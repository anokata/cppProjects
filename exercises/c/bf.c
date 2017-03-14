#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//optarg

#define BF_MEMORY_SIZE 30000
#define BF_LOOPS_SIZE 1000
typedef struct Machine {
    uint8_t *data; 
    uint8_t dp; // Data pointer
    char *code; 
    uint8_t ip; // Instruction pointer 
    uint8_t ii; // Output index
    char *input;
    uint8_t input_size;
    uint8_t oi; // Output index
    char *output;
    uint32_t *loops;
    uint32_t code_size;
} Machine;

Machine* make_machine(char* code, char* input) {
    Machine* m = malloc(sizeof(Machine));
    m->data = malloc(BF_MEMORY_SIZE);
    m->loops = calloc(1, BF_LOOPS_SIZE);
    memset(m->loops, 0, BF_LOOPS_SIZE);
    m->dp = 0;
    m->ip = 0;
    m->oi = 0;
    m->ii = 0;
    m->code = code;
    m->code_size = strlen(code);
    m->output = malloc(100);
    m->input = input;
    m->input_size = strlen(input);

    uint32_t *loop_stack = malloc(BF_LOOPS_SIZE);
    int l = 0;
    for (int i = 0; i < strlen(code); i++) {
        if (code[i] == '[') {
            loop_stack[l++] = i;
        }
        if (code[i] == ']') {
            l--;
            m->loops[loop_stack[l]] = i;
            m->loops[i] = loop_stack[l];
        }
    }
    free(loop_stack);

    return m;
}

void down_machine(Machine* m) {
    free(m->output);
    free(m->loops);
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
    printf("Loops: [%p]:  ", m->loops);
    for (int i = 0; i < BF_LOOPS_SIZE/sizeof(uint32_t); i++) {
        if (m->loops[i] && i < m->loops[i]) {
            printf("%d->%d  ", i, m->loops[i]);
        }
    }
    printf("\n");
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
    if (m->ii < m->input_size) {
        m->data[m->dp] = m->input[m->ii++];
    } else {
        m->data[m->dp] = 0;
    }
}

void machine_cmd_loop_start(Machine* m) {
    if (m->data[m->dp] == 0) {
        m->ip = m->loops[m->ip];
    }
}

void machine_cmd_loop_end(Machine* m) {
    if (m->data[m->dp] != 0) {
        m->ip = m->loops[m->ip];
    }
}

void machine_step(Machine* m) {
    switch (m->code[m->ip]) {
        case '>':
            machine_cmd_dpinc(m);
            break;
        case '<':
            machine_cmd_dpdec(m);
            break;
        case '+':
            machine_cmd_datainc(m);
            break;
        case '-':
            machine_cmd_datadec(m);
            break;
        case '.':
            machine_cmd_out(m);
            break;
        case ',':
            machine_cmd_in(m);
            break;
        case '[':
            machine_cmd_loop_start(m);
            break;
        case ']':
            machine_cmd_loop_end(m);
            break;
    }
    m->ip++;
}

void test_instructions(Machine* m) {
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
}

void machine_run(Machine* m) {
    while (m->ip < m->code_size) {
        machine_step(m);
        print_machine(m);
        usleep(100000);
    }
}

typedef void (*cmd_func)(Machine*);

typedef struct {
    char cmd[30];
    cmd_func func;
} Command;
Command commands[] = {
    {"run", machine_run}
};

cmd_func find_cmd_func(char *cmd) {
    for (int i = 0; i < sizeof(commands); i++) {
        if (strcmp(commands[i].cmd, cmd) == 0) {
            return commands[i].func;
        }
    }
    return NULL;
}

#define INPUT_BUF 200
void repl() {
    static const char promt[] = " > ";
    static const char help[] = "Possible commands: \n\trun\texit";
    printf("%s\n", help);
    printf("%s", promt);

    char buf[INPUT_BUF];
    fgets(buf, INPUT_BUF, stdin);
    char cmd[INPUT_BUF];
    char arg1[INPUT_BUF];
    sscanf(buf, "%s %s", cmd, arg1);
    // cmd func find()
    cmd_func f = find_cmd_func(cmd);
    if (f) {
        printf("! %p\n", f);
    } else {
        printf("! Not Found!");
    }

}

void test_m() {
    char input[] = "some\xFF";
    char code[] = ",+[-.,+]";
    Machine* m = make_machine(code, input);
    printf("> Machine maked.\n");
    repl();
    //machine_run(m);
    //test_instructions(m);
    //print_machine(m);
    down_machine(m);
}

//TODO: interactive commands: view state, make step, run, reset, break at, 
// mem edit, input edit, code edit, loops view colors, Exec instruction
int main(int argc, char** argv) {
    printf("Brainfuck interpreter v 0.0 (q)\n");
    test_m();
    printf("Quited.");
    return 0;
}
