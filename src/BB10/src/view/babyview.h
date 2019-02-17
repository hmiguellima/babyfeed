#ifndef BABYVIEW_H
#define BABYVIEW_H

#include "view/view.h"
#include "../BabyFeedApp.hpp"
#include "model/eventmodel.h"

class BabyView : public View
{
    Q_OBJECT
public:
    BabyView(BabyFeedApp* dView, QObject* parent);

    QString url();
    QString viewName();

    QString getPhotoUrl();
    void setPhotoUrl(QString url);
    QString getName();
    void setName(QString name);
    QDate getBirthday();
    void setBirthday(QDate birthday);
    int getGenderIndex();
    void setGenderIndex(int index);
    bool isTimerAlarmsActive();
    void setTimerAlarmsActive(bool active);
    int getTimerInterval();
    void setTimerInterval(int interval);
    void setBabyId(int id);
    void setAge(QString age);
    void setMeasures(QString measures);
    void setEventList(QList<PEvent>* events);
    void setEventsDate(QString date);

    void newBaby();

signals:
    void saveBaby();
    void cancel();
    void deleteBaby();
    void photoCaptured();
    void registerTimerEvent();
    void registerManualEvent();
    void editEvent(int eventId);
    void deleteEvent(int eventId);
    void showReports();
    void prevDayBtnClicked();
    void nextDayBtnClicked();
    void prevMonthBtnClicked();
    void nextMonthBtnClicked();

public slots:
    void handleActivation();

private slots:
	void handleDelete();
	void handleSave();
    void handlePhotoClicked();
    void handleTimerClicked();
    void handleManualEventClicked();
    void handleCancel();
    void handleEditEvent(int eventId);
    void handleDeleteEvent(int eventId);
    void handleReports();
    void handlePrevDateClicked();
    void handleNextDateClicked();
    void handlePrevMonthClicked();
    void handleNextMonthClicked();

private:
    EventModel* _eventsModel;
};

#endif // BABYVIEW_H
