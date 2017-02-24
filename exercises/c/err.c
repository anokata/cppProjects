#include <string.h>
#include <unistd.h>

void error_test() {
    for (int i = 0; i < 10; i++) {
        char* str = strerror(i);
        int len = strlen(str);
        write(1, str, len);
        write(1, "\n", 2);
    }
    perror("Error> ");
}

int main() {
    return 0;
}
