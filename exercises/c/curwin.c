#include <ncurses.h>
#include <stdio.h>
int main() {
	initscr();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_YELLOW);
	init_pair(3, COLOR_GREEN, COLOR_WHITE);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(4));
	refresh();
    int width = getmaxx(stdscr);
    int heigth = getmaxy(stdscr);

	WINDOW* win1 = newwin(heigth/1, width/2, 0, 0);
	wattron(win1, 0);
	wbkgdset(win1, COLOR_PAIR(4)  | ' ');
	wclear(win1);
    for (int i=0; i< heigth*width/1; i++) {
        //wprintw(win1, ". ");
        wclrtoeol(win1);
    }
    box(win1, 0, 0);
    wmove(win1, 1, 1);
	wprintw(win1, "somenewwindowtex");
    refresh();
	wrefresh(win1);

	int ch = getch();
	//chtype a = 'a' | A_BOLD | COLOR_PAIR(1);
	while(ch != 'q') {
		clear();
		if (ch != '\t');

		mvprintw(0, 0, "q = exit;");
		refresh();
		ch = getch();
	}

	endwin();
	printf("%d:%d", width, heigth/2 - 1);
	return 0;
}
