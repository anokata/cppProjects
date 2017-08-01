#include <stdio.h>
#define INWORD 1
#define OUTWORD 0

int main() { 
    printf("Words: \n");
    int c_count = 0;
    int w_count = 0;
    int l_count = 0;
    int state = INWORD;
    int c = getchar();
    while (c != EOF) {
        if (c == '\n') ++l_count;
        ++c_count;
        if (state == INWORD) {
            putchar(c);
            if (c == ' ' || c == '\t' || c == '\n') {
                state = OUTWORD;
                ++w_count;
            }
        } else {
            putchar('\n');
            if (c != ' ' && c != '\n' && c != '\t') {
                putchar(c);
                state = INWORD;
            }
        }
        c =getchar();
    }

    printf("\n");
    printf("bytes(%d) ", c_count);
    printf("lines(%d) ", l_count);
    printf("words(%d) ", w_count);

    printf("\n");
}
