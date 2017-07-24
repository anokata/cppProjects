#include "ccurses.h"
#include "state.h"

enum States {State_run, State_end,  NUM_STATES};
enum Events {Event_draw, Event_key,  NUM_EVENTS};
/* GLOBAL */
State state;

void cc_printi(uint32_t value, struct Color color) {
    char str[20];
    snprintf(str, 20, "%d", value);
    cc_print(str, color);
}

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
        ss_handle(state, Event_draw, 0);

        /* curses_allwin_refresh(m); */
		ch = getch();
	}
}

void curses_end() {
	endwin();
}



int draw(void* data) {
    cc_putxy('D', cb_yellow, 3, 2);
    return 0;
}


void state_init() {
    state = ss_make_state(NUM_STATES, NUM_EVENTS);
    ss_sethander(state, State_run, Event_draw, draw);
    ss_setstate(state, State_run);
}

void start() {
    curses_init();
		cc_putxy('X', cd_yellow, 1, 2);
		cc_print("\nW:H = ", cd_red);
        cc_printi(width, cd_white);
		cc_print(" : ", cd_red);
        cc_printi(heigth, cd_white);
    state_init();

    processInput();
    ss_free_state(state);
    curses_end();
}
