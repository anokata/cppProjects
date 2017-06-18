#pragma once
#ifndef __STATE__
#define __STATE__
#include <map>

typedef void (*Handler)();
typedef std::map<std::string, Handler> Event;
typedef std::map<std::string, Event> State_table;

void t() {}

class State {

    State() {
        //this->state_table = new State_table;
        //Event e = std::map("x", &t);
        //this->state_table.insert(std::make_pair("test", Event));
    }

public:
    void add_state(std::string name);
    //void add_event(std::string name);
    void bind_event(std::string state, std::string event, Handler handler);

    /* state:(event: handler) */
    State_table state_table;
};

#endif
