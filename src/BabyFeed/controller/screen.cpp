#include "screen.h"
#include "mainwindow.h"

Screen::Screen(MainWindow* window) : QWidget(window), view(0)
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
}

void Screen::setView(View *view)
{
    if (this->view !=0)
        this->view->deleteLater();

    this->view=view;
}

View * Screen::getView()
{
    return view;
}

void Screen::setTitle(QString title)
{
    view->setTitle(title);
}

QString Screen::getViewUrl()
{
    if (view!=0)
        return view->url();
    else {
        qDebug("Screen::getViewUrl:uninitialized view");
        return "";
    }
}

void Screen::notifyActive()
{
    if (view!=0) {
        view->notifyActive();
        viewReadyHandler();
    }
}

