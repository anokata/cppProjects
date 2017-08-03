#include <stdlib.h>

// Escapes
#define RED "\033[0;30m" // 7 chars len
#define BLUE "\033[0;34m"
#define DEFAULT "\033[0;37m"

enum Weather { WTHR_SUNNY, WTHR_FOG, WTHR_RAIN };

typedef struct Sky {
    int hour;
    enum Weather weather;
    int width;
} *Sky;


Sky make_sky();
void free_sky(Sky s);

char *sky_draw_string(Sky s);
char *sky_draw_cc(Sky s, int x, int y);
