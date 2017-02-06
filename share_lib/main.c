#include "hello.h"

int main() {
    hello_message("John");
    return 0;
}
//gcc main.c -L. -lHello -o hello
//run as: LD_LIBRARY_PATH=. ./hello
