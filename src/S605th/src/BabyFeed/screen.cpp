#include "screen.h"
#include "mainwindow.h"

Screen::Screen(MainWindow* window) :
        QWidget(window)
{
    this->window=window;
}

MainWindow* Screen::getWindow()
{
    return window;
}

void Screen::show()
{
    window->showScreen(this);
    showHandler();
}
