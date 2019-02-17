#include "checkinoutview.h"

CheckInOutView::CheckInOutView(BabyFeedApp* dView, QObject* parent) : View(dView, parent)
{
}

QString CheckInOutView::url()
{
	return "checkinout";
}

QString CheckInOutView::viewName()
{
    return "checkInOutScreen";
}


void CheckInOutView::setTimerText(QString text) {
    mainItem()->setProperty("timerText", text);
}

void CheckInOutView::setEventTypeIndex(int index) {
	mainItem()->setProperty("eventIndex", index);
}

int CheckInOutView::getEventTypeIndex() {
	return mainItem()->property("eventIndex").toInt();
}

void CheckInOutView::setRunning(bool isRunning) {
	mainItem()->setProperty("running", isRunning);
}

void CheckInOutView::handleActivation()
{
    connect(mainItem(), SIGNAL(startClicked()), this, SLOT(handleStartClicked()));
    connect(mainItem(), SIGNAL(stopClicked()), this, SLOT(handleStopClicked()));
}

void CheckInOutView::handleStartClicked()
{
    emit startClicked();
}

void CheckInOutView::handleStopClicked()
{
    emit stopClicked();
}
