#include "level_gen.h"

#include <iostream>
/* Map chars definition */
// ?

char random_char() {
    switch (std::rand() % 5) {
        case 0: return '.';
        case 1: return '#';
        case 2: return '#';
        case 3: return '#';
        case 4: return ' ';
    }
    return ' ';
}

int neighbours(CharMap cm, Point p) {
    int n = 0;
    char current_char = cm[p];
    for (int i = -1; i < 2; i++) {
        for (int k = -1; k < 2; k++) {
            if (cm[Point(i + p.first, k + p.second)] == current_char) {
                n++;
            }
        }
    }
    return n;
}

template <typename T> Map<T> step_generation(Map<T> &cm) {
    std::cout << cm.width;
    for (int i = 1; i < cm.width; i++) {
        for (int k = 1; k < cm.height; k++) {
                /* cm.dots[Point(i, k)] = random_char(); */
            if (neighbours(cm.dots, Point(i, k)) < 5) {
                cm.dots[Point(i, k)] = ' ';
            }
            if (neighbours(cm.dots, Point(i, k)) > 7) {
                cm.dots[Point(i, k)] = ' ';
            }
        }
    }
    return cm;
}

CharsMap generate() {
    std::srand(unsigned(std::time(0)));
    CharMap cm;
    int w = 30;
    for (int i = 1; i < w; i++) {
        for (int k = 1; k < w; k++) {
            cm[Point(i, k)] = random_char();
        }
    }
    CharsMap map;
    map.dots = cm;
    map.width = w;
    map.height = w;
    step_generation(map);

    return map;
}
