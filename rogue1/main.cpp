#include "app.h"

int main() {
    CursesWrapper::load(new App());
    CursesWrapper::start();
    return 0;
}
