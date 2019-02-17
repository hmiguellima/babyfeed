#include "global.h"
#include "babyscreen.h"
#include "model/eventbus.h"
#include "model/nobaby.h"
#include <QList>
#include <QBuffer>
#include <QDataStream>
#include <QDate>
#include <QFile>
#include <QtDebug>
#include "../BabyFeedApp.hpp"
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeTargetReply>
#include <QtGui/QImage>

using namespace bb::system;

BabyScreen::BabyScreen(BabyFeedApp* window) :
    Screen(window)
{
    view=new BabyView(window, this);
    setView(view);

    invokeManager = new InvokeManager(this);
    date=QDate::currentDate();

    connect(EventBus::getInstance(), SIGNAL(showBabyScreen(Baby&)), this, SLOT(onShowBabyScreen(Baby&)));
    connect(view, SIGNAL(saveBaby()), this, SLOT(saveBaby()));
    connect(view, SIGNAL(photoCaptured()), this, SLOT(handlePhotoClicked()));
    connect(view, SIGNAL(cancel()), this, SLOT(updateBabyView()));
    connect(view, SIGNAL(deleteBaby()), this, SLOT(deleteBaby()));
    connect(view, SIGNAL(registerTimerEvent()), this, SLOT(handleTimerClicked()));
    connect(view, SIGNAL(registerManualEvent()), this, SLOT(handleManualEventClicked()));
    connect(view, SIGNAL(editEvent(int)), this, SLOT(handleEditEvent(int)));
    connect(view, SIGNAL(deleteEvent(int)), this, SLOT(handleDeleteEvent(int)));
    connect(view, SIGNAL(showReports()), this, SLOT(handleShowReports()));
    connect(view, SIGNAL(prevDayBtnClicked()), this, SLOT(showPrevDay()));
    connect(view, SIGNAL(nextDayBtnClicked()), this, SLOT(showNextDay()));
    connect(view, SIGNAL(prevMonthBtnClicked()), this, SLOT(showPrevMonth()));
    connect(view, SIGNAL(nextMonthBtnClicked()), this, SLOT(showNextMonth()));
    connect(invokeManager, SIGNAL(childCardDone(const bb::system::CardDoneMessage&)), this, SLOT(handleChildCardDone(const bb::system::CardDoneMessage&)));
}

void BabyScreen::viewReadyHandler()
{
	if (baby.getGender()==NewBaby)
    	view->newBaby();
	else
	    updateBabyView();
}

BabyScreen::~BabyScreen()
{
}

void BabyScreen::onShowBabyScreen(Baby &baby)
{
    if (baby.getGender()==NewBaby)
        this->baby=NoBaby();
    else
        this->baby=baby;
    show();
}

void BabyScreen::saveBaby()
{
    bool newBaby=(baby.getGender()==NewBaby);
    QString homeDir = QDir::currentPath();

    baby.setName(view->getName());
    if (view->getGenderIndex()==1)
        baby.setGender(Girl);
    else
        baby.setGender(Boy);

    baby.setBirthDate(QDateTime(view->getBirthday()));
    baby.setFeedAlarmActive(view->isTimerAlarmsActive());
    baby.setTimeBetweenFeeds(view->getTimerInterval());
    baby.setSelected(true);

    baby.persist();

    // Vamos gravar a foto
    if (view->getPhotoUrl().startsWith("asset")) {
    	if (QFile::exists(Baby::getPhotoFileName(baby)))
    		QFile::remove(Baby::getPhotoFileName(baby));
    	if (view->getGenderIndex()==0)
    		QFile::copy(homeDir+"/app/native/assets/images/baby_boy_icon.png", Baby::getPhotoFileName(baby));
    	else
    		QFile::copy(homeDir+"/app/native/assets/images/baby_girl_icon.png", Baby::getPhotoFileName(baby));
    } else
    	if (view->getPhotoUrl().endsWith("tmpPhoto.jpg")) {
        	if (QFile::exists(Baby::getPhotoFileName(baby)))
        		QFile::remove(Baby::getPhotoFileName(baby));
    		QFile::copy(appDataPath + "/tmpPhoto.jpg", Baby::getPhotoFileName(baby));
    	}

    updateBabyView();

    if (newBaby)
        EventBus::getInstance()->fireBabyAdded(baby);
    else
        EventBus::getInstance()->fireBabyUpdated(baby);
}

void BabyScreen::handlePhotoClicked() {
	InvokeRequest request;

	request.setTarget("sys.camera.card");
	request.setAction("bb.action.CAPTURE");
	request.setData("photo");

	invokeManager->invoke(request);
}

void BabyScreen::updateBabyView() {
	updateTitle();
	view->setName(baby.getName());
	view->setAge(baby.getAge());
	view->setMeasures(baby.getLastMeasures());
	view->setBirthday(baby.getBirthDate().date());
	view->setTimerAlarmsActive(baby.isFeedAlarmActive());
	view->setGenderIndex(baby.getGender());
	view->setTimerInterval(baby.getTimeBetweenFeeds());

	view->setPhotoUrl("file://" + appDataPath + "/dummy.jpg");
	view->setPhotoUrl(Baby::getPhotoUri(baby));

    events=baby.listEvents(date, date);
	view->setEventList(&events);

	updateCurrentDateLabel();
}

void BabyScreen::updateTitle() {
    setTitle(baby.getName()+tr("'s Events"));
}

void BabyScreen::deleteBaby() {
	baby.remove();
}

void BabyScreen::handleTimerClicked() {
	EventBus::getInstance()->fireShowCheckInOutScreen(baby);
}

void BabyScreen::handleManualEventClicked() {
	EventBus::getInstance()->fireShowManualEventScreen(baby);
}

void BabyScreen::handleEditEvent(int eventId) {
	PEvent event;

	event=BabyEvent::getById(baby, eventId);
	EventBus::getInstance()->fireShowEventInfo(event);
}

void BabyScreen::handleShowReports() {
	EventBus::getInstance()->fireShowReportScreen(baby);
}

void BabyScreen::handleChildCardDone(const bb::system::CardDoneMessage& message) {
	if (message.reason()=="save") {
		QString url=message.data();
		QImage photo;

		photo.load(url);
		photo.scaled(240, 240, Qt::KeepAspectRatioByExpanding).save(appDataPath + "/tmpPhoto.jpg");

		view->setPhotoUrl("file://" + appDataPath + "/dummy.jpg");
		view->setPhotoUrl("file://" + appDataPath + "/tmpPhoto.jpg");
	}
}

void BabyScreen::updateCurrentDateLabel() {
    view->setEventsDate(QLocale().toString(date, tr("ddd, MMM/dd/yyyy")));
}

void BabyScreen::showNextDay() {
    date=date.addDays(1);
    updateCurrentDateLabel();

    events=baby.listEvents(date, date);
	view->setEventList(&events);
}

void BabyScreen::showPrevDay() {
    date=date.addDays(-1);
    updateCurrentDateLabel();

    events=baby.listEvents(date, date);
	view->setEventList(&events);
}

void BabyScreen::showNextMonth() {
    date=date.addMonths(1);
    updateCurrentDateLabel();

    events=baby.listEvents(date, date);
	view->setEventList(&events);
}

void BabyScreen::handleDeleteEvent(int eventId) {
	PEvent event;

	event=BabyEvent::getById(baby, eventId);
	event->remove();

	updateBabyView();
}

void BabyScreen::showPrevMonth() {
    date=date.addMonths(-1);
    updateCurrentDateLabel();

    events=baby.listEvents(date, date);
	view->setEventList(&events);
}
