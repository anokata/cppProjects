#include "lib/ccurses.h"
#include "sky_view.h"
#include <string.h>

Sky make_sky() {
    Sky s = malloc(sizeof(struct Sky));
    s->hour = 12;
    s->width = 10;
    return s;
}


void free_sky(Sky s) {
    free(s);
}

char *sky_draw_string(Sky s) {
    int escape_space = 7 * 2;
    int len = s->width + escape_space;
    char *str = malloc(len);
    memset(str, ' ', len - 1);
    str[0] = '[';
    /* strcat(str + 1, RED); */
    str[8] = 'X';

    str[len - 1] = ']';
    return str;
}
