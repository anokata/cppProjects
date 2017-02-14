#include <QtGui>
#include <QPushButton>
#include <QTextStream>
#include "window.h"
 
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Window window;
    window.setFixedSize(200, 250);
    window.show();
    QTextStream(stdout) << "Started!" << endl;
    int result = app.exec();
    QTextStream(stdout) << "End." << endl;
    return result;
}
 
