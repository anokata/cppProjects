#pragma once
#include "curses_app.h"
#include "window.h"
#include <unistd.h>

class CursesWrapper {
    public:
    static int QUIT_KEY;
    static CursesApp *app;
    static Window *window;

    static WINDOW *init();
    static void end();
    static int main_loop();
    static void update();
    static void load(CursesApp *app);
    static void start();
};
