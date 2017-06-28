#pragma once
#ifndef __STATE__
#define __STATE__
#include <map>
#include <functional>

//typedef void (*Handler)();
typedef std::function<void(void)> Handler;
/* Event = {'name': func, ...} */
typedef std::map<std::string, Handler> Event;
/* State_table = { 'statename': event } */
typedef std::map<std::string, Event> State_table;

//void t() {}

class State {

public:
    State() {
        //this->state_table = new State_table;
        //Event e = std::map("x", &t);
        //this->state_table.insert(std::make_pair("test", Event));
    }

    //void add_state(std::string name);
    //void add_event(std::string name);
    void bind_event(std::string state, std::string event, Handler handler);

    /* state:(event: handler) */
    State_table state_table;
    void change(std::string state);
    void handle(std::string event);
    std::string state;
};

#endif
