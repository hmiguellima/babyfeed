#include "screen.h"
#include "../BabyFeedApp.hpp"

Screen::Screen(BabyFeedApp* window) : view(0)
{
    this->window=window;
}

BabyFeedApp* Screen::getWindow()
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

void Screen::notifyInactive() {
	emit screenInactive();
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

