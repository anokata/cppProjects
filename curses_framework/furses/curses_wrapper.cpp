#include <ncurses.h>
#include "curses_wrapper.h"
#include "window.h"

#define DELAY_H 1
#define DELAY 1

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

int CursesWrapper::update() {
    erase();
    app->update();
    refresh();
    return 0;
}

int CursesWrapper::main_loop() {
	int key = 0;
    bool is_end = false;
    halfdelay(DELAY_H);
    while (!is_end) {
        is_end = CursesWrapper::update() != 0;
        key = getch();
        is_end = is_end || key == QUIT_KEY;
        is_end = is_end || app->key_handler(key);
        usleep(DELAY);
    }
    return 0;
}

WINDOW *CursesWrapper::init() {
	WINDOW *win = initscr();
    keypad(win, TRUE);
    noecho();
    curs_set(0);
    use_default_colors(); /* fror transparend -1 as back*/
	start_color();
    return win;
}

void CursesWrapper::end() {
    app->finalize();
    delete window;
	endwin();
}
