#include "ccurses.h"

void cc_print(char *str, struct Color color) {
	attron(color.attr);
    attron(COLOR_PAIR(color.color));
	printw(str);
	attroff(color.attr);
    attroff(COLOR_PAIR(color.color));
}

void cc_printxy(char *str, struct Color color, int x, int y) {
    move(y, x);
	attron(color.attr);
    attron(COLOR_PAIR(color.color));
	printw(str);
	attroff(color.attr);
    attroff(COLOR_PAIR(color.color));
}

void cc_put(char ch, struct Color color) {
	attron(color.attr);
    attron(COLOR_PAIR(color.color));
	addch(ch);
	attroff(color.attr);
    attroff(COLOR_PAIR(color.color));
}

void cc_putxy(char ch, struct Color color, int x, int y) {
    move(y, x);
	attron(color.attr);
    attron(COLOR_PAIR(color.color));
	addch(ch);
	attroff(color.attr);
    attroff(COLOR_PAIR(color.color));
}

void curses_init() {
	initscr();
    use_default_colors(); /* fror transparend -1 as back*/
	start_color();
	cc_init_colors();
	refresh();
    width = getmaxx(stdscr);
    heigth = getmaxy(stdscr);
    curs_set(0);
    move(1, 0);
}

void processInput() {
	int ch = getch();
	while(ch != 'q') {
		clear();
        /* cmd_func f = find_char_func(ch); */
        /* if (f) { */
        /*     f(m); */
        /* } */
		/* putc(ch, 1); */
		cc_print("hi some", cb_blue);

        /* curses_allwin_refresh(m); */
		ch = getch();
	}
}

void curses_end() {
	endwin();
}

void start() {
    curses_init();
		cc_print("hi some", cb_white);
		cc_print("hi some", cb_blue);
		cc_print("hi some", cn_blue);
		cc_print("hi some", cd_blue);
		cc_print("hi some", cb_red);
		cc_print("hi some", cn_red);
		cc_print("hi some", cd_red);
		cc_putxy('X', cb_yellow, 2, 2);
		cc_putxy('X', cn_yellow, 3, 2);
		cc_putxy('X', cd_yellow, 1, 2);
    processInput();
    curses_end();
}
