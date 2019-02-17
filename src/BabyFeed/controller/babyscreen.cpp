#include "global.h"
#include "babyscreen.h"
#include "mainwindow.h"
#include "model/eventbus.h"
#include <QList>
#include <QBuffer>
#include <QDataStream>
#include <QImage>
#include <QIcon>
#include <QPixmap>
#include <QDate>
#include <QDeclarativeContext>
#include <QFile>
#include <QtDebug>

BabyScreen::BabyScreen(MainWindow* window) :
    Screen(window)
{
    contactsModel=new ContactsModel(this);
    window->rootContext()->setContextProperty("contactsModel", contactsModel);

    view=new BabyView(window, this);
    setView(view);

    connect(EventBus::getInstance(), SIGNAL(showBabyScreen(Baby&)), this, SLOT(onShowBabyScreen(Baby&)));
    connect(view, SIGNAL(canceled()), window, SLOT(showMainScreen()));
    connect(view, SIGNAL(save()), this, SLOT(saveBaby()));
    connect(view, SIGNAL(notificationChanged(int,QString)), this, SLOT(handleNotificationChange(int,QString)));
    connect(contactsModel, SIGNAL(contactsLoaded()), this, SLOT(handleContactsLoaded()));
}

void BabyScreen::viewReadyHandler()
{
    photoCaptured=false;

    if (baby.getGender()!=NewBaby)
        setTitle(baby.getName()+tr("'s File"));
    else
        setTitle(tr("New Baby's File"));

    if (baby.getGender()==NewBaby)
    {
        view->setName("");
        view->setBirthday(QDate::currentDate());
        view->setGenderIndex(0);
        view->setTimerAlarmsActive(true);
        view->setTimerInterval(120);
        view->setNewBaby(true);
    }
    else
    {
        view->setName(baby.getName());
        view->setBirthday(baby.getBirthDate().date());
        view->setPhotoUrl(Baby::getPhotoUri(baby));
        if (baby.getGender()==Boy)
            view->setGenderIndex(0);
        else
            view->setGenderIndex(1);
        view->setTimerAlarmsActive(baby.isFeedAlarmActive());
        view->setTimerInterval(baby.getTimeBetweenFeeds());
        view->setNewBaby(false);
    }
    contactsModel->setNotified(&baby);
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
    //getWindow()->showBusyBox();
    show();
}

void BabyScreen::saveBaby()
{
    bool newBaby=(baby.getGender()==NewBaby);

    if (view->getName().trimmed().length()==0)
    {
        getWindow()->showMessageBox(tr("BabyFeed"), tr("Baby's name is invalid"));
        return;
    }
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

    if (view->isPhotoChanged())
    {
        QFile::remove(Baby::getPhotoFileName(baby));
        bool res=QFile::copy(view->getCapturedDataPath(), Baby::getPhotoFileName(baby));
        qDebug() << "Photo changed:"+Baby::getPhotoFileName(baby)+"|"+(res?"1":"0");
    }
    else
    {
        qDebug() << "Photo unchanged";
        if (newBaby)
        {
            QImage photo;

            if (baby.getGender()==Boy)
                photo=QImage(":/icons/icons/baby_boy_icon.png");
            else
                photo=QImage(":/icons/icons/baby_girl_icon.png");
            photo.save(Baby::getPhotoFileName(baby));
        }
    }

    if (newBaby)
        EventBus::getInstance()->fireBabyAdded(baby);
    else
        EventBus::getInstance()->fireBabyUpdated(baby);
}


void BabyScreen::handleNotificationChange(int index, QString type)
{
    QString contactKey=contactsModel->getContactKeyFromRow(index);
    char notfType;

    if (type!="")
       getWindow()->showMessageBox(tr("BabyFeed"), tr("There might be a cost involved with the sending of the sms, depending on your operator contract."));

    if (type=="")
        notfType=0;
    else
        notfType=type.toAscii().at(0);

    switch (notfType)
    {
        case 0:
            baby.removeNotification(contactKey);
            contactsModel->setNotification(index, false);
            break;
        case 'F':
            baby.updateNotfication(contactKey, 'F');
            contactsModel->setNotification(index, true);
            break;
        case 'M':
            baby.updateNotfication(contactKey, 'M');
            contactsModel->setNotification(index, true);
            break;
        case 'P':
            baby.updateNotfication(contactKey, 'P');
            contactsModel->setNotification(index, true);
            break;
        case 'B':
            baby.updateNotfication(contactKey, 'B');
            contactsModel->setNotification(index, true);
            break;
    }
}

void BabyScreen::handleContactsLoaded()
{
    //getWindow()->hideBusyBox();
    //qDebug() << "Contacts loaded";
}

