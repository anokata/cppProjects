#include "app.h"

enum States {State_run, State_end, State_wmap,  NUM_STATES};
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
//+1.1 Struct for wmap
//+1.2 Load wmap.
//+1.3 View wmap. (color regions) 
//+1.3.1 wmap mode.
// 1.4 show map region description.
// 1.5 gettext _
// 2. local map, coords to wmap, load regions, moving, store, load

void processInput(WorldMap wmap) {
    ss_handle(state, Event_draw, wmap);
	int ch = getch();
	while(ch != 'q') {
        ss_handle(state, Event_key, (void*)(uint64_t)ch);
        ss_handle(state, Event_draw, wmap);
		ch = getch();
	}
}

int key_run(void* data) {
    char key = (uint64_t)data;
    cc_printi(key, cd_green);
    switch (key) {
        case 'w':
            ss_setstate(state, State_wmap);
            break;
    }
    return 0;
}

int draw(void* data) {
    clear();
    /* cc_putxy('D', cb_yellow, 3, 2); */
    cc_printxy("Key bindings:\nw world map\nh this help\n", cb_white, 0, 0);
    return 0;
}

int wmap_key(void* data) {
    char key = (uint64_t)data;
    switch (key) {
        case 'h':
            ss_setstate(state, State_run);
            break;
    }
    return 0;
}
int wmap_draw(void* data) {
    clear();
    cc_putxy('M', cb_yellow, 3, 2);
    print_wmap(data);
    return 0;
}

void state_init() {
    state = ss_make_state(NUM_STATES, NUM_EVENTS);
    ss_sethander(state, State_run, Event_draw, draw);
    ss_sethander(state, State_run, Event_key, key_run);
    ss_sethander(state, State_wmap, Event_draw, wmap_draw);
    ss_sethander(state, State_wmap, Event_key, wmap_key);
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
        WorldMap wmap = load_wmap();

    processInput(wmap);
    ss_free_state(state);
    curses_end();
        free_wmap(wmap);
        free_map(world);
}
