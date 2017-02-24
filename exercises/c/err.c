#include <string.h> // strlen?
#include <unistd.h> // write
#include <stdio.h> // fprintf
#include <errno.h> // errno
extern char **environ;

void error_test() {
    for (int i = 0; i < 10; i++) {
        char* str = strerror(i);
        int len = strlen(str);
        write(1, str, len);
        write(1, "\n", 2);
    }
    perror("Error> ");
    //fprintf(stdin, "mem>> %s\n", strerror(ENOMEM));
    errno = ENOMEM;
    perror("self: ");
    for (int i = 0; i < 10; i++) {
        errno = i*i;
        char* str = strerror(i);
        int len = strlen(str);
        perror("this: ");
    }
}

void env_test() {
    for (int i = 0; i < 3; i++) {
        if (environ[i] != NULL)
            printf("env[%d] : %s\n", i, environ[i]);
    }
}

int main(int argc, char* argv[], char* envp[]) {
    error_test();
    env_test();
    return 0;
}
