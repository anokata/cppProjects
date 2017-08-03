#include "sky_view.h"
#include <stdio.h>

int main(void) {
    printf(DEFAULT);
    printf("sky:\n");
    Sky s = make_sky();
    char *str = sky_draw_string(s);
    printf("%s\n", str);
    printf("zzz");

    free(str);
    free_sky(s);
    printf(DEFAULT);
}
