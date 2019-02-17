#ifndef CHECKINOUTSCREEN_H
#define CHECKINOUTSCREEN_H

#include <QTimer>
#include <QTime>
#include <QDateTime>
#include "screen.h"
#include "model/event.h"
#include "model/baby.h"
#include "view/checkinoutview.h"

class BabyFeedApp;

class CheckInOutScreen : public Screen
{
    Q_OBJECT

public:
    explicit CheckInOutScreen(BabyFeedApp* window);
    ~CheckInOutScreen();

public slots:
    void viewReadyHandler();

private:
    static const int LEFT=0;
    static const int BOTTLE=1;
    static const int RIGHT=2;

    CheckInOutView* view;
    QTimer *timer;
    QDateTime startDateTime;
    Baby baby;

    void addAlarm(PEvent& event);
    void initTime();

private slots:
    void onShowCheckInOutScreen(Baby &baby);
    void handleStart();
    void handleStop();
    void displayTime();
    void handleInactive();
};

#endif // CHECKINOUTSCREEN_H
