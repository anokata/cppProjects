
enum Weather { WTHR_SUNNY, WTHR_FOG, WTHR_RAIN };

typedef struct Sky {
    int hour;
    enum Weather weather;
} Sky;
