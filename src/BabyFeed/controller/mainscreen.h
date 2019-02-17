#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "screen.h"
#include "model/eventmodel.h"
#include "model/event.h"
#include <QAbstractListModel>
#include <QModelIndex>
#include "model/baby.h"
#include <QHash>
#include <QDate>
#include "view/mainview.h"
#include <QDeclarativeView>
#include "model/nobaby.h"
#include "model/contactsmodel.h"

class MainWindow;

class MainScreen : public Screen
{
    Q_OBJECT

public:
    MainScreen(MainWindow* window);
    ~MainScreen();

    Baby getCurrentBaby();

signals:
    void babyListBuilt();

public slots:
    void viewReadyHandler();

private:
    QDate date;
    MainView* view;
    QList<Baby> babyList;
    QList<PEvent > eventsList;
    int currentBabyIndex;
    NoBaby noBaby;
    ContactsModel* contactsModel;

    void toogleButtons(bool enable);
    void updateWindowTitle();
    void clearBabySelection();
    void updateCurrentDateLabel();

private slots:
    void buildBabyListView();
    void babySelected(Baby &baby);
    void babyAdded(Baby &baby);
    void babyUpdated(Baby &baby);
    void babyDeleted(Baby &baby);
    void showCheckInOutScreen();
    void showManualEventScreen();
    void updateEventModelAndShow(PEvent &event);
    void showEventInfo(PEvent &event);
    void showNextDay();
    void showPrevDay();
    void removeEventRow(int row);
    void showReportScreen();
    void scrollToSelectedBaby();
    void handleDataReset();
    void handleBabyPageChange(int index);
    void handleDateChanged(QDate date);
    void handleUncheckEvent(int index);
    void handleCheckEvent(int index);
    void handleEditEvent(int index);
    void handleDeleteEvent(int index);
    void handleEditBaby(int index);
    void handleDeleteBaby(int index);
    void handleNewBaby();
    void handleEventsChanged();
};

#endif // MAINSCREEN_H
