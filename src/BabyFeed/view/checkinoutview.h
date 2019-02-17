#ifndef CHECKINOUTVIEW_H
#define CHECKINOUTVIEW_H

#include "view/view.h"
#include "mainwindow.h"
#include <QDate>
#include <QTime>

class CheckInOutView : public View
{
    Q_OBJECT
public:
    CheckInOutView(MainWindow* dView, QObject* parent);

    QString url();
    QString viewName();
    void setTotalTimerText(QString text);
    void setParcialTimerText(QString text);

signals:
    void eventCanceled();
    void startStopClicked();
    void leftFeedClicked();
    void bottleClicked();
    void rightFeedClicked();
    void endEvents();

public slots:
    void handleActivation();
    void handleEventCanceled();
    void handleStartStopClicked();
    void handleLeftFeedClicked();
    void handleBottleClicked();
    void handleRightFeedClicked();
    void handleEndEvents();
};

#endif // CHECKINOUTVIEW_H
