#include <QtGui>
#include <QPushButton>
#include <QTextStream>
#include "window.h"
 
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QTextStream(stdout) << "Started!" << endl;
    Window window;
    window.show();
    int result = app.exec();
    QTextStream(stdout) << "End." << endl;
    return result;
}
 
