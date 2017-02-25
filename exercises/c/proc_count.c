#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"

int compare_and_count_name(char* content) {
    static char name[] = "tmux";
    static int count = 0;
    if (strcmp(content, name) == 0) {
        count++;
    }
    return count;
}

int proc_dir(char* fn, int(*fun)(char*)) {
    int res = 0;
    static char path[] = "/proc/";
    char filename[256];
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir: ");
        return 0;
    }
    struct dirent* cur;
    cur = readdir(dir);
    while (cur) {
        if (is_digit_name(cur->d_name)) {
            sprintf(filename, "/proc/%s/%s", cur->d_name, fn);
            char* content = read_onestr_file(filename);
            if (content) {
                res = fun(content);
            }
        }
        cur = readdir(dir);
    }
    if (closedir(dir)) {
        perror("closedir: ");
        return 0;
    }
    return res;
}

int main() {
    int count = proc_dir("comm", compare_and_count_name);
    printf("%d\n", count);
    return 0;
}
