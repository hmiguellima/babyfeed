#include "manualeventview.h"

ManualEventView::ManualEventView(BabyFeedApp* dView, QObject* parent) : View(dView, parent)
{
}

QString ManualEventView::url()
{
	return "manualevent";
}

QString ManualEventView::viewName()
{
    return "manualEventScreen";
}

void ManualEventView::handleActivation()
{
    connect(mainItem(), SIGNAL(save()), this, SLOT(handleSave()));
    connect(mainItem(), SIGNAL(deleteEvent()), this, SLOT(handleDelete()));
}

void ManualEventView::setEventTypeIndex(int index)
{
    mainItem()->setProperty("eventTypeIndex", QVariant(index));
}

int ManualEventView::getEventTypeIndex()
{
    return mainItem()->property("eventTypeIndex").toInt();
}

void ManualEventView::setStartDate(QDate date)
{
    mainItem()->setProperty("startDate", QVariant(date));
}

QDate ManualEventView::getStartDate()
{
    return mainItem()->property("startDate").toDate();
}

void ManualEventView::setStartTime(QTime time)
{
    mainItem()->setProperty("startTime", QVariant(QDateTime(QDate::currentDate(), time)));
}

QTime ManualEventView::getStartTime()
{
    return mainItem()->property("startTime").toTime();
}

void ManualEventView::setDuration(int duration)
{
    mainItem()->setProperty("duration", duration);
}

int ManualEventView::getDuration()
{
    return mainItem()->property("duration").toInt();
}

void ManualEventView::setGeneralNotes(QString notes)
{
    mainItem()->setProperty("generalNotes", notes);
}

QString ManualEventView::getGeneralNotes()
{
    return mainItem()->property("generalNotes").toString();
}

void ManualEventView::setMedicineName(QString name)
{
    mainItem()->setProperty("medicineName", name);
}

QString ManualEventView::getMedicineName()
{
    return mainItem()->property("medicineName").toString();
}

void ManualEventView::setMedicineNotes(QString notes)
{
    mainItem()->setProperty("medicineNotes", notes);
}

QString ManualEventView::getMedicineNotes()
{
    return mainItem()->property("medicineNotes").toString();
}

// Measurements

void ManualEventView::setWeight(int weight)
{
    mainItem()->setProperty("mWeight", ((qreal)weight)/100);
}

int ManualEventView::getWeight()
{
    return (int)(mainItem()->property("mWeight").toReal()*100);
}

void ManualEventView::setHeight(int height)
{
    mainItem()->setProperty("mHeight", ((qreal)height)/100);
}

int ManualEventView::getHeight()
{
    return (int)(mainItem()->property("mHeight").toReal()*100);
}

void ManualEventView::setCephalic(int cephalic)
{
    mainItem()->setProperty("mCephalic", ((qreal)cephalic)/100);
}

int ManualEventView::getCephalic()
{
    return (int)(mainItem()->property("mCephalic").toReal()*100);
}

void ManualEventView::handleSave()
{
    emit save();
}

void ManualEventView::setInterval(int hours)
{
    mainItem()->setProperty("interval", hours);
}

int ManualEventView::getInterval()
{
    return mainItem()->property("interval").toInt();
}

void ManualEventView::setEndDate(QDate date)
{
    mainItem()->setProperty("endDate", date);
}

QDate ManualEventView::getEndDate()
{
    return mainItem()->property("endDate").toDate();
}

void ManualEventView::setStartDateEnabled(bool enabled)
{
    mainItem()->setProperty("startDateEnabled", enabled);
}

void ManualEventView::setStartTimeEnabled(bool enabled)
{
    mainItem()->setProperty("startTimeEnabled", enabled);
}

void ManualEventView::setEventTypeBtnRowEnabled(bool enabled)
{
    mainItem()->setProperty("eventTypeBtnRowEnabled", enabled);
}

void ManualEventView::setRecurrenceVisible(bool visible)
{
    mainItem()->setProperty("recurrenceVisible", visible);
}

void ManualEventView::handleDelete() {
	emit deleteEvent();
}
