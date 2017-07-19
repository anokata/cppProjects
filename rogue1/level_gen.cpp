#include "level_gen.h"

char random_char() {
    switch (std::rand() % 3) {
        case 0: return '.';
        case 1: return '#';
        case 2: return '-';
    }
    return ' ';
}

int neighbours(CharMap cm, Point p) {

    return 0;
}

template <typename T> Map<T> step_generation(Map<T> cm) {
    for (int i = 1; i < cm.width; i++) {
        for (int k = 1; k < cm.height; k++) {
            //cm.dots[Point(i, k)] = random_char();
        }
    }
}

CharsMap generate() {
    CharMap cm;
    for (int i = 1; i < 20; i++) {
        for (int k = 1; k < 20; k++) {
            cm[Point(i, k)] = random_char();
        }
    }
    CharsMap map;
    map.dots = cm;

    return map;
}
