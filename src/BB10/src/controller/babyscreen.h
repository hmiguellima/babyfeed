#ifndef BABYSCREEN_H
#define BABYSCREEN_H

#include "screen.h"
#include "model/baby.h"
#include "model/event.h"
#include <QList>
#include "model/notification.h"
#include "view/babyview.h"
#include <bb/system/InvokeManager>
#include <bb/system/CardDoneMessage>

class BabyFeedApp;

class BabyScreen : public Screen
{
    Q_OBJECT

public:
    explicit BabyScreen(BabyFeedApp* window);
    ~BabyScreen();

public slots:
    void viewReadyHandler();

private:
    QDate date;
    Baby baby;
    BabyView* view;
    QList<PEvent> events;
    bb::system::InvokeManager* invokeManager;

    void updateCurrentDateLabel();

private slots:
    void onShowBabyScreen(Baby &baby);
    void saveBaby();
    void deleteBaby();
    void updateTitle();
    void updateBabyView();
    void handlePhotoClicked();
    void handleTimerClicked();
    void handleManualEventClicked();
    void handleEditEvent(int eventId);
    void handleDeleteEvent(int eventId);
    void handleShowReports();
    void handleChildCardDone(const bb::system::CardDoneMessage& message);
    void showNextDay();
    void showPrevDay();
    void showNextMonth();
    void showPrevMonth();
};

#endif // BABYSCREEN_H
