#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QImage>
#include <QLabel>

class QPushButton;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    QPushButton *exit_button;
    //Inventory *inventory;
    QTableWidget *inventory;
    QImage image;
    QLabel *imageLabel;

signals:

public slots:

private:
    bool loadFile(const QString &fileName);
};

#endif // WINDOW_H
