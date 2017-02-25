#include <unistd.h> // write
#include <stdio.h> // fprintf
#include <errno.h> // errno
#include <stdlib.h> // getenv atexit

void fork_fun(void(*daemon_func)(), void(*parent_func)(pid_t pid)) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork: ");
        return;
    }
    if (pid == 0) { // child
        daemon_func();
        exit(0);
    } else { // parent
        parent_func(pid);
        exit(0);
    }
}

void parent_func(pid_t pid) {
    printf("%d\n", pid);
}

void daemon_func() {
    chdir("/");
    if (setsid() == -1) {
        perror("setsid: ");
        return;
    }
    fclose(stdin);
    fclose(stderr);
    //int i = 3;
    fclose(stdout);
    //while(i--) usleep(500000);
    while(1) usleep(500000);
}

void demonize() {
    fork_fun(daemon_func, parent_func);
}

int main(int argc, char* argv[], char* envp[]) {
    demonize();
    return 0;
}
