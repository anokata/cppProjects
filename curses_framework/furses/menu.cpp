#include "menu.h"


void Menu::add(std::string item, Runner fun) {
    items.push_back(MenuItem(item, fun));
}

int Menu::select() {
    return items[index].second();
}

void Menu::next() {
    index = (index + 1) % items.size();
}

void Menu::back() {
    if (index == 0) {
        index = items.size() - 1;
    } else {
        index--;
    }
}

void Menu::draw(Window *window) {
    int x = window->left;
    int y = window->top;
    int index = 0;
    for (auto item : items) {
        y++;
        if (this->index == index) {
            window->print(item.first, color::bwhite, x, y);
        } else {
            window->print(item.first, color::nwhite, x, y);
        }
        index++;
    }
}

