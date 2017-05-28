#include <ncurses.h>
#include "curses_wrapper.h"

int CursesWrapper::QUIT_KEY = 'q';
CursesApp *CursesWrapper::app;

void CursesWrapper::load(CursesApp *app) {
    CursesWrapper::app = app;
}

void CursesWrapper::start() {
    WINDOW *win = CursesWrapper::init();
    CursesWrapper::main_loop(win);
    CursesWrapper::end();
}

void CursesWrapper::update() {
    erase();
    app->update();
    refresh();
}

int CursesWrapper::main_loop(WINDOW *win) {
	int key = 0;
    bool is_end = false;
    while (!is_end) {
        CursesWrapper::update();
        key = getch();
        is_end = key == QUIT_KEY;
        app->key_handler(key);
    }
    return 0;
}

WINDOW *CursesWrapper::init() {
	WINDOW *win = initscr();
    keypad(win, TRUE);
    noecho();
	start_color();
init_pair (1, COLOR_RED, COLOR_BLACK);
init_pair (2, COLOR_BLUE, COLOR_BLACK);
    return win;
}

void CursesWrapper::end() {
	endwin();
}
