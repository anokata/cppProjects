#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

struct sockaddr_in local;

int server() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    int cs;
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(1234);
    local.sin_family = AF_INET;
    int result = bind(s, (struct sockaddr*) &local, sizeof(local));
    if (result) {
        perror("bind");
        return 0;
    }
    listen(s, 5);
    cs = accept(s, NULL, NULL);

    char buf[50];
    read(cs, buf, 29); //recv
    printf("(server recv) %s\n", buf);
    close(cs);
    return 0;
}

int client() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(1234);
    local.sin_family = AF_INET;
    //int result = bind(s, (struct sockaddr*) &local, sizeof(local));
    connect(s, (struct sockaddr*) &local, sizeof(local));
    char buf[50] = "(client send) client connected\n";
    write(s, buf, strlen(buf) + 1); //send
    close(s);
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 0;
    }
    //struct sockaddr_in local;
    if (argv[1][0] == 's') {
        server();
    } else { 
        client();
    }
    return 0;
}
