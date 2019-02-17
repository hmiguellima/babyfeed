#include <QtGui/QApplication>
#include "mainwindow.h"
#include "global.h"

int main(int argc, char *argv[])
{
    //QApplication::setGraphicsSystem("openvg");
    QApplication app(argc, argv);
    MainWindow *window=0;
    int execV;

    window=new MainWindow();
    execV=app.exec();
    if (window) delete window;

    return execV;
}
