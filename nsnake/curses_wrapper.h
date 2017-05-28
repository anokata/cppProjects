#pragma once
#include "curses_app.h"

class CursesWrapper {
    public:
    static int QUIT_KEY;
    static CursesApp *app;

    static WINDOW *init();
    static void end();
    static int main_loop(WINDOW *win);
    static void update();
    static void load(CursesApp *app);
    static void start();
};
