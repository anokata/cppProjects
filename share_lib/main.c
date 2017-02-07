#include "hello.h"
#include <stdio.h>
#include <stddef.h>
#include "solution.h"

int main() {
    hello_message("John");
    char *s = "Str";
    int a = 8;
    int b;
    b = stringStat(s, 2, &a);
    printf("\n b = %i a = %i\n", b, a);
    return 0;
}
//gcc main.c -L. -lHello -o hello
//run as: LD_LIBRARY_PATH=. ./hello
