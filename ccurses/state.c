#include "state.h"

State ss_make_state(uint32_t states_count, uint32_t events_count) {
    State state = malloc(sizeof(State));
    state->table = calloc(states_count * events_count, sizeof(void*));
    state->num_states = states_count;
    state->num_events = events_count;
    state->current_state = 0;
    return state;
}

void ss_free_state(State s) {
    free(s->table);
    free(s);
}

void ss_sethander(State state, int state_id, int event, StateFunction fun) {
    state->table[state_id + (event * state->num_events)] = fun;
}

StateFunction ss_gethandler(State state, int event) {
    return state->table[state->current_state + (event * state->num_events)];
}

int ss_handle(State state, int event, void *data) {
    return state->table[state->current_state + (event * state->num_events)](data);
}

void ss_setstate(State state, int new_state) {
    state->current_state = new_state;
}

