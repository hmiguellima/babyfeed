#include "mainscreen.h"
#include <QSharedPointer>
#include "model/nobaby.h"
#include <QList>
#include "model/eventbus.h"
#include <QSharedPointer>
#include "model/emptyevent.h"
#include <QDate>
#include "../BabyFeedApp.hpp"
#include <QLocale>

#define MAX_BABIES 10

MainScreen::MainScreen(BabyFeedApp* window) :
    Screen(window)
{
    view=new MainView(window, this);
    setView(view);

    connect(view, SIGNAL(showBabyPage(int)), this, SLOT(handleShowBabyPage(int)));
    connect(view, SIGNAL(deleteBaby(int)), this, SLOT(handleDeleteBaby(int)));
}

MainScreen::~MainScreen()
{
}

void MainScreen::viewReadyHandler()
{
    view->setTitle(tr("BabyFeed - My Babies"));
    updateMainView();
}

void MainScreen::updateMainView() {
	babies=Baby::list();
    view->setBabyList(&babies);
    if (babies[0].getId()==-1)
    	getWindow()->showMessageBox("BabyFeed", "Welcome to BabyFeed! \nPlease start by adding a new baby.");
}

void MainScreen::handleShowBabyPage(int babyId)
{
	view->showDummyPhotos();
    if (babyId!=-1) {
	    Baby baby=Baby::getBabyById(babyId);
	    EventBus::getInstance()->fireShowBabyScreen(baby);
	}
	else
	    EventBus::getInstance()->fireShowBabyScreen(noBaby);
}

void MainScreen::handleDeleteBaby(int babyId) {
    Baby baby=Baby::getBabyById(babyId);
    baby.remove();
    updateMainView();
}



