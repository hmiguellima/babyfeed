#include "manualeventview.h"

ManualEventView::ManualEventView(MainWindow* dView, QObject* parent) : View(dView, parent)
{

}

QString ManualEventView::url()
{
#if defined(MEEGO_VERSION)
    return "qrc:/qml/qml/BabyFeedMeego/ManualEventPage.qml";
#else
    return "qrc:/qml/qml/BabyFeedSymbian/ManualEventPage.qml";
#endif
}

QString ManualEventView::viewName()
{
    return "manualEventScreen";
}

void ManualEventView::handleActivation()
{
    connect(mainItem(), SIGNAL(canceled()), this, SLOT(handleEventCanceled()));
    connect(mainItem(), SIGNAL(save()), this, SLOT(handleSave()));
}

void ManualEventView::handleEventCanceled()
{
    emit eventCanceled();
}

void ManualEventView::setEventTypeIndex(int index)
{
    QMetaObject::invokeMethod(mainItem(), "setEventTypeIndex", Q_ARG(QVariant, index));
    //mainItem()->setProperty("eventTypeIndex", QVariant(index));
}

int ManualEventView::getEventTypeIndex()
{
    return mainItem()->property("eventTypeIndex").toInt();
}

void ManualEventView::setStartDate(QDate date)
{
    mainItem()->setProperty("startDateDay", date.day());
    mainItem()->setProperty("startDateMonth", date.month());
    mainItem()->setProperty("startDateYear", date.year());
}

QDate ManualEventView::getStartDate()
{
    int day;
    int month;
    int year;

    day=mainItem()->property("startDateDay").toInt();
    month=mainItem()->property("startDateMonth").toInt();
    year=mainItem()->property("startDateYear").toInt();

    return QDate(year,month,day);
}

void ManualEventView::setStartTime(QTime time)
{
    mainItem()->setProperty("startTimeHour", time.hour());
    mainItem()->setProperty("startTimeMinute", time.minute());
}

QTime ManualEventView::getStartTime()
{
    QTime time;
    int hour;
    int minute;

    hour=mainItem()->property("startTimeHour").toInt();
    minute=mainItem()->property("startTimeMinute").toInt();

    return QTime(hour, minute);
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
    mainItem()->setProperty("endDateDay", date.day());
    mainItem()->setProperty("endDateMonth", date.month());
    mainItem()->setProperty("endDateYear", date.year());
}

QDate ManualEventView::getEndDate()
{
    int day;
    int month;
    int year;

    day=mainItem()->property("endDateDay").toInt();
    month=mainItem()->property("endDateMonth").toInt();
    year=mainItem()->property("endDateYear").toInt();

    return QDate(year,month,day);
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
