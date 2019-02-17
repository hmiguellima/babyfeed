#ifndef CHECKINOUTSCREEN_H
#define CHECKINOUTSCREEN_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QAction>
#include "screen.h"
#include "event.h"
#include "baby.h"

namespace Ui {
    class CheckInOutScreen;
}

class MainWindow;

class CheckInOutScreen : public Screen
{
    Q_OBJECT

public:
    explicit CheckInOutScreen(MainWindow* window);
    ~CheckInOutScreen();

public slots:
    void displayTime();
    void startTimer();
    void stopTimer();
    void typeButtonClicked(int type);

protected:
    virtual void showHandler();

private:
    static const int LEFT=0;
    static const int BOTTLE=1;
    static const int RIGHT=2;

    Ui::CheckInOutScreen *ui;
    QTimer *timer;
    QTime startTime;
    int elapsedSecs;
    QDateTime startDateTime;
    char type;
    Baby baby;
    QAction *startAction;
    QAction *stopAction;

    void addAlarm(PEvent& event);

private slots:
    void onShowCheckInOutScreen(Baby &baby);
};

#endif // CHECKINOUTSCREEN_H
