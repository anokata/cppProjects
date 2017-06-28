#include <ncurses.h>
#include "curses_wrapper.h"
#include "window.h"

#define DELAY_H 8
#define DELAY 50

// Vars
int CursesWrapper::QUIT_KEY = 'q';
CursesApp *CursesWrapper::app;
Window *CursesWrapper::window;

void CursesWrapper::load(CursesApp *app) {
    CursesWrapper::app = app;
    WINDOW *win = CursesWrapper::init();
    window = new Window(win);
    app->window = window;
    app->init();
}

void CursesWrapper::start() {

    CursesWrapper::main_loop();
    CursesWrapper::end();
}

void CursesWrapper::update() {
    erase();
    app->update();
    refresh();
}

int CursesWrapper::main_loop() {
	int key = 0;
    bool is_end = false;
    halfdelay(DELAY_H);
    while (!is_end) {
        CursesWrapper::update();
        key = getch();
        is_end = key == QUIT_KEY;
        app->key_handler(key);
        usleep(DELAY);
    }
    return 0;
}

WINDOW *CursesWrapper::init() {
	WINDOW *win = initscr();
    keypad(win, TRUE);
    noecho();
    curs_set(0);
	start_color();
init_pair (1, COLOR_RED, COLOR_BLACK);
init_pair (2, COLOR_BLUE, COLOR_BLACK);
    return win;
}

void CursesWrapper::end() {
    app->finalize();
    delete window;
	endwin();
}
