#include "babyview.h"
#include <QtCore/QtCore>

BabyView::BabyView(BabyFeedApp* dView, QObject* parent) : View(dView, parent)
{
	_eventsModel=new EventModel(this);

    dView->rootContext()->setContextProperty("eventsModel", _eventsModel);
}

QString BabyView::url()
{
	return "baby";
}

QString BabyView::viewName()
{
    return "babyScreen";
}

void BabyView::handleActivation()
{
    connect(mainItem(), SIGNAL(saveBaby()), this, SLOT(handleSave()));
    connect(mainItem(), SIGNAL(capturePhotoClicked()), this, SLOT(handlePhotoClicked()));
    connect(mainItem(), SIGNAL(cancel()), this, SLOT(handleCancel()));
    connect(mainItem(), SIGNAL(deleteBaby()), this, SLOT(handleDelete()));
    connect(mainItem(), SIGNAL(timerEventClicked()), this, SLOT(handleTimerClicked()));
    connect(mainItem(), SIGNAL(manualEventClicked()), this, SLOT(handleManualEventClicked()));
    connect(mainItem(), SIGNAL(editEventClicked(int)), this, SLOT(handleEditEvent(int)));
    connect(mainItem(), SIGNAL(deleteEventClicked(int)), this, SLOT(handleDeleteEvent(int)));
    connect(mainItem(), SIGNAL(reportsClicked()), this, SLOT(handleReports()));
    connect(mainItem(), SIGNAL(prevDateClicked()), this, SLOT(handlePrevDateClicked()));
    connect(mainItem(), SIGNAL(nextDateClicked()), this, SLOT(handleNextDateClicked()));
    connect(mainItem(), SIGNAL(prevMonthClicked()), this, SLOT(handlePrevMonthClicked()));
    connect(mainItem(), SIGNAL(nextMonthClicked()), this, SLOT(handleNextMonthClicked()));
}

void BabyView::handleSave()
{
    emit saveBaby();
}

QString BabyView::getPhotoUrl()
{
    return mainItem()->property("photoUrl").toString();
}

void BabyView::setPhotoUrl(QString url)
{
    mainItem()->setProperty("photoUrl", url);
}

QString BabyView::getName()
{
    return mainItem()->property("name").toString();
}

void BabyView::setName(QString name)
{
    mainItem()->setProperty("name", name);
}

QDate BabyView::getBirthday()
{
    return mainItem()->property("birthday").toDate();
}

void BabyView::setBirthday(QDate birthday)
{
    mainItem()->setProperty("birthday", QVariant(birthday));
}

int BabyView::getGenderIndex()
{
    return mainItem()->property("gender").toInt();
}

void BabyView::setGenderIndex(int index)
{
    mainItem()->setProperty("gender", index);
}

bool BabyView::isTimerAlarmsActive()
{
    return mainItem()->property("timerEnabled").toBool();
}

void BabyView::setTimerAlarmsActive(bool active)
{
    mainItem()->setProperty("timerEnabled", active);
}

int BabyView::getTimerInterval()
{
    return mainItem()->property("minutes").toInt();
}

void BabyView::setTimerInterval(int interval)
{
    mainItem()->setProperty("minutes", interval);
}

void BabyView::newBaby() {
	setBabyId(-1);
	setName("");
	setPhotoUrl("asset:///images/baby_boy_icon.png");
	setBirthday(QDate::currentDate());
	setGenderIndex(0);
	setTimerAlarmsActive(true);
	setTimerInterval(60);

	QMetaObject::invokeMethod(mainItem(), "newBaby");
}

void BabyView::setBabyId(int id) {
    mainItem()->setProperty("babyId", id);
}

void BabyView::setAge(QString age) {
	mainItem()->setProperty("age", age);
}

void BabyView::setMeasures(QString measures) {
	mainItem()->setProperty("measures", measures);
}

void BabyView::handlePhotoClicked() {
	emit photoCaptured();
}

void BabyView::setEventList(QList<PEvent>* events) {
	_eventsModel->setEvents(events);
}

void BabyView::handleDelete() {
	emit deleteBaby();
}

void BabyView::handleTimerClicked() {
	emit registerTimerEvent();
}

void BabyView::handleManualEventClicked() {
	emit registerManualEvent();
}

void BabyView::handleCancel() {
	emit cancel();
}

void BabyView::handleEditEvent(int eventId) {
	emit editEvent(eventId);
}

void BabyView::setEventsDate(QString date) {
    mainItem()->setProperty("currentDate", QVariant(date));
}

void BabyView::handleReports() {
	emit showReports();
}

void BabyView::handlePrevDateClicked() {
	emit prevDayBtnClicked();
}

void BabyView::handleNextDateClicked() {
	emit nextDayBtnClicked();
}

void BabyView::handlePrevMonthClicked() {
	emit prevMonthBtnClicked();
}

void BabyView::handleDeleteEvent(int eventId) {
	emit deleteEvent(eventId);
}

void BabyView::handleNextMonthClicked() {
	emit nextMonthBtnClicked();
}




