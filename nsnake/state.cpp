#include "state.h"

void State::bind_event(std::string state, std::string event, Handler handler) {
    state_table[state][event] = handler;
}

void State::change(std::string state) {
    // TODO check if in dict
    this->state = state;
}

void State::handle(std::string event) {
    auto f = state_table[state][event];
    if (f != NULL) {
        f();
    }
}
