#include "widget.h"

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QSlider>
#include <QSpinBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
