#include "babyview.h"
#include <QDeclarativeContext>

BabyView::BabyView(MainWindow* dView, QObject* parent) : View(dView, parent)
{

}

QString BabyView::url()
{
#if defined(MEEGO_VERSION)
    return "qrc:/qml/qml/BabyFeedMeego/BabyPage.qml";
#else
    return "qrc:/qml/qml/BabyFeedSymbian/BabyPage.qml";
#endif
}

QString BabyView::viewName()
{
    return "babyScreen";
}

void BabyView::handleActivation()
{
    connect(mainItem(), SIGNAL(canceled()), this, SLOT(handleCancel()));
    connect(mainItem(), SIGNAL(save()), this, SLOT(handleSave()));
    connect(mainItem(), SIGNAL(notificationChanged(int,QString)), this, SLOT(handleNotificationChanged(int,QString)));
}

void BabyView::handleCancel()
{
    emit canceled();
}

void BabyView::handleSave()
{
    emit save();
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
    int day;
    int month;
    int year;

    day=mainItem()->property("birthdayDay").toInt();
    month=mainItem()->property("birthdayMonth").toInt();
    year=mainItem()->property("birthdayYear").toInt();

    return QDate(year,month,day);
}

void BabyView::setBirthday(QDate birthday)
{
    mainItem()->setProperty("birthdayDay", birthday.day());
    mainItem()->setProperty("birthdayMonth", birthday.month());
    mainItem()->setProperty("birthdayYear", birthday.year());
}

int BabyView::getGenderIndex()
{
    return mainItem()->property("genderIndex").toInt();
}

void BabyView::setGenderIndex(int index)
{
    mainItem()->setProperty("genderIndex", index);
}

bool BabyView::isTimerAlarmsActive()
{
    return mainItem()->property("timerAlarmsEnabled").toBool();
}

void BabyView::setTimerAlarmsActive(bool active)
{
    mainItem()->setProperty("timerAlarmsEnabled", active);
}

int BabyView::getTimerInterval()
{
    return mainItem()->property("minutesInterval").toInt();
}

void BabyView::setTimerInterval(int interval)
{
    mainItem()->setProperty("minutesInterval", interval);
}

void BabyView::handleNotificationChanged(int index, QString type)
{
    emit notificationChanged(index, type);
}

void BabyView::setNewBaby(bool isNew)
{
    mainItem()->setProperty("newBaby", isNew);
}

bool BabyView::isPhotoChanged()
{
    return mainItem()->property("photoChanged").toBool();
}


QString BabyView::getCapturedDataPath()
{
    return mainItem()->property("capturedPhotoPath").toString();
}

