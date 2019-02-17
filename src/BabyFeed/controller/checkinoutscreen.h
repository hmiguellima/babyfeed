#ifndef CHECKINOUTSCREEN_H
#define CHECKINOUTSCREEN_H

#include <QTimer>
#include <QTime>
#include <QDateTime>
#include "screen.h"
#include "model/event.h"
#include "model/baby.h"
#include "view/checkinoutview.h"
#include "model/contactsmodel.h"

class MainWindow;

class CheckInOutScreen : public Screen
{
    Q_OBJECT

public:
    explicit CheckInOutScreen(MainWindow* window);
    ~CheckInOutScreen();

public slots:
    void viewReadyHandler();

private:
    static const int LEFT=0;
    static const int BOTTLE=1;
    static const int RIGHT=2;

    CheckInOutView* view;
    QTimer *timer;
    QTime startTime;
    int totalElapsedSecs;
    int elapsedSecs;
    QDateTime startDateTime;
    char type;
    Baby baby;
    PEvent event;
    ContactsModel* contactsModel;

    void addAlarm(PEvent& event);
    void initTime();
    void resetTime();

private slots:
    void onShowCheckInOutScreen(Baby &baby);
    void notifyEvent();
    void handleStartStop();
    void displayTime();
    void startTimer();
    void stopTimer();
    void typeButtonClicked(int type);
    void leftClicked();
    void bottleClicked();
    void rightClicked();
};

#endif // CHECKINOUTSCREEN_H
