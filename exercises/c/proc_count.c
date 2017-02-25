#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

int is_digit_name(char *str) {
    while(*str) {
        if (isdigit(*str))
            return -1;
        str++;
    }
    return 0;
}

char* read_onestr_file(char *filename) {
    FILE *fd = fopen(filename, "r");
    if (!fd) {
        perror("open file: ");
        return NULL;
    }
    static char buf[256];
    char* res = fgets(buf, 255, fd);
    if (!res) {
        perror("read file: ");
        return NULL;
    }
    buf[strlen(buf) - 1] = '\0';
    return buf;

    if (!fclose(fd)) {
        perror("close file: ");
        return NULL;
    }
}

int main() {
    char name[] = "genenv";
    char path[] = "/proc/";
    char filename[256];
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir: ");
        return 0;
    }

    struct dirent* cur;
    cur = readdir(dir);
    int count = 0;
    while (cur) {
        if (is_digit_name(cur->d_name)) {
            sprintf(filename, "/proc/%s/comm", cur->d_name);
            char* content = read_onestr_file(filename);
            if (content) {
                if (strcmp(content, name) == 0) {
                    count++;
                }
            }
        }
        cur = readdir(dir);
    }


    printf("%d\n", count);
    if (closedir(dir)) {
        perror("closedir: ");
        return 0;
    }
    return 0;
}
