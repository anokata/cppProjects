#include <string.h> // strlen?
#include <unistd.h> // write
#include <stdio.h> // fprintf
#include <errno.h> // errno
#include <stdlib.h> // getenv atexit
//#include <fcntl.h> // how to get file attr? stat?
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
    printf("%s\n", getenv("PWD"));
    printf("%s\n", getenv("TERM"));
}

char *name = "         ";
void exit_func() {
    printf("exit function call after exit of %s\n", name);
}

void buf_stream_test() {
    setbuf(stdout, NULL); // disable buffering for stdout
    putc('a', stdout);
    putc('b', stdout);
    putc('\n', stdout);
    setbuf(stdin, NULL); // disable buffering 
    char c = getchar();
    printf("code=%d\n", c);
}

int main(int argc, char* argv[], char* envp[]) {
    error_test();
    env_test();
    atexit(exit_func);
    int pid = fork();
    if (pid == -1) {
        perror("fork: ");
        return 0;
    }
    if (pid == 0) {
        printf("I am child.\n");
        name = "child";
    } else {
        printf("I am parent of %d.\n", pid);
        name = "parent";
    }
    return 0;
}
