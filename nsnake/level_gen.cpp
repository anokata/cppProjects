#include "level_gen.h"

char random_char() {
    switch (std::rand() % 3) {
        case 0: return '.';
        case 1: return '#';
        case 2: return '-';
    }
}

// cm step_generation(CharMap cm)

CharMap generate() {
    CharMap cm;
    for (int i = 1; i < 20; i++) {
        for (int k = 1; k < 20; k++) {
            cm[Point(i, k)] = random_char();
        }
    }

    return cm;
}
