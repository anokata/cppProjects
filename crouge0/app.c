#include "app.h"

enum States {State_run, State_end,  NUM_STATES};
enum Events {Event_draw, Event_key,  NUM_EVENTS};
/* GLOBAL */
State state;

// menu (not up down - use vi like.)
// ascii art pic editor mode, terminal again vi keys... + animation.
// Idea and world First! get old records and generate mechanic
// First - fun therefore slash like dia
// but not clone dia.
// 2. Magic and skill grows like morow
// 3. World height? it difficult for first try, lets it be simple dung with wild
// 4. Draw static map, weather zones, caves. Circle
// 5. fun events, fast grow, new challanges, FF, skills/items (keys, levitate, lava, swim) for access areas, bosses
// 6. end goal, meaning of all of this - survive and escape from planet. from black entitys.
// 1. World map, how store, view it with self position. map blocks. view frame.
// 1.1 Struct for wmap
// 1.2 Load wmap.
// 1.3 View wmap. (color regions) wmap mode.
// 1.4 show map region description.
// 1.5 gettext _
// 2. local map, coords to wmap, load regions, moving, store, load

void processInput() {
	int ch = getch();
	while(ch != 'q') {
        ss_handle(state, Event_draw, 0);
        ss_handle(state, Event_key, (void*)(uint64_t)ch);
		ch = getch();
	}
}

int key_run(void* data) {
    char key = (uint64_t)data;
    cc_printi(key, cd_green);
    return 0;
}

int draw(void* data) {
    clear();
    cc_putxy('D', cb_yellow, 3, 2);
    return 0;
}


void state_init() {
    state = ss_make_state(NUM_STATES, NUM_EVENTS);
    ss_sethander(state, State_run, Event_draw, draw);
    ss_sethander(state, State_run, Event_key, key_run);
    ss_setstate(state, State_run);
}

void start() {
    curses_init();
		cc_putxy('W', cd_yellow, 1, 2);
		cc_print("\nWid:Hei = ", cd_blue);
        cc_printi(width, cd_white);
		cc_print(" : ", cd_red);
        cc_printi(heigth, cd_white);
    state_init();
    Map world = load_map("world.map");

    processInput();
    ss_free_state(state);
    curses_end();

    free_map(world);
}
