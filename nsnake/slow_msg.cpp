#include "slow_msg.h"
#include <string>

bool SlowMsg::draw(Window *window) {
    std::string str = msg.substr(0, frame);
    frame++;
    curs_set(1);
    if (frame >= msg.size()) {
        curs_set(0);
    }
    window->print(str.c_str(), color::nwhite, 0, 1);
    return false;
}
