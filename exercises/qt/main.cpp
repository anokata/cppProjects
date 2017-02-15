#include <QtGui>
#include <QPushButton>
#include "window.h"
 
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    int result = app.exec();
    return result;
}
 
