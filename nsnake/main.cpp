#include <iostream>
#include <ncurses.h>

WINDOW *init();
void end();
int main_loop(WINDOW *win);

int main() {
    WINDOW *win = init();
    main_loop(win);
    end();
    return 0;
}

void update() {
    erase();

    move(1, 1);
    attron(COLOR_PAIR(1));
    addch('a' | A_BOLD);
    attroff(COLOR_PAIR(1));

    refresh();
}

int main_loop(WINDOW *win) {
	int ch = 0;
    bool is_end = false;
    while (!is_end) {
        update();
        ch = getch();
        is_end = ch == 'q';
    }
    return 0;
}

class App { // static?
};

WINDOW *init() {
	WINDOW *win = initscr();
    keypad(win, TRUE);
    noecho();
	start_color();
init_pair (1, COLOR_RED, COLOR_BLACK);
init_pair (2, COLOR_BLUE, COLOR_BLACK);
    return win;
}

void end() {
	endwin();
}
