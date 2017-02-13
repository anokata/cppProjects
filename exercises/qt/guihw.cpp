#include <QtGui>
#include <QPushButton>
#include "window.h"
 
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Window window;
    window.show();

    /*
    QWidget window;
    window.setFixedSize(100, 50);
    
    QLabel label("Hello, world!", &window);
    label.show();
    QPushButton button("_", &window);
    button.setText("My text");
    button.setToolTip("A tooltip");
    button.show();
    QFont font ("Courier");
    button.setFont(font);
    button.setIcon(QIcon::fromTheme("face-smile"));
    button.setGeometry(10, 10, 80, 30);
    window.show();
    */
    return app.exec();
}
 
