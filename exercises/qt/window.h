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
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    QPushButton *exit_button;
    QTableWidget *inventory;
    QImage image;
    QLabel *imageLabel;

signals:

public slots:

private:
    bool loadFile(const QString &fileName);
};

#endif // WINDOW_H
