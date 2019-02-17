#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "view/view.h"
#include "model/eventmodel.h"
#include "model/baby.h"
#include <QList>
#include <QDate>
#include "mainwindow.h"
#include <QObject>
#include "model/babiesmodel.h"

class MainView : public View
{
    Q_OBJECT
public:
    MainView(MainWindow* dView, QObject* parent);

    void setEventsList(QList<PEvent >* events);
    void setBabyList(QList<Baby>* babies);
    void setSelectedBaby(int index);
    void setEventsDate(QString date);
    void refreshBaby(int index);

    QString url();
    QString viewName();
    void setCurrentBabyIndex(int index);

public slots:
    void handleActivation();

signals:
    void babyChanged(int index);
    void prevDayBtnClicked();
    void nextDayBtnClicked();
    void dateSelected(QDate date);
    void timerBtnClicked();
    void eventBtnClicked();
    void reportBtnClicked();
    void checkEventClicked(int index);
    void uncheckEventClicked(int index);
    void editEventClicked(int index);
    void deleteEventClicked(int index);
    void editBabyClicked(int index);
    void deleteBabyClicked(int index);
    void newBabyClicked();

private:
    BabiesModel* _babiesModel;
    EventModel* _eventModel;

private slots:
    void handleBabyChanged(int index);
    void handlePrevDateClicked();
    void handleNextDateClicked();
    void handleDateChanged(int year, int month, int day);
    void handleCheckEventClicked(int index);
    void handleUncheckEventClicked(int index);
    void handleEditEventClicked(int index);
    void handleDeleteEventClicked(int index);
    void handleTimerEventClicked();
    void handleManualEventClicked();
    void handleReportClicked();
    void handleEditBaby(int index);
    void handleDeleteBaby(int index);
    void handleNewBaby();
};

#endif // MAINVIEW_H
