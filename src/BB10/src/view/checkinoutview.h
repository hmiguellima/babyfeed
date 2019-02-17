#ifndef CHECKINOUTVIEW_H
#define CHECKINOUTVIEW_H

#include "view/view.h"
#include "../BabyFeedApp.hpp"
#include <QDate>
#include <QTime>

class CheckInOutView : public View
{
    Q_OBJECT
public:
    CheckInOutView(BabyFeedApp* dView, QObject* parent);

    QString url();
    QString viewName();

    void setTimerText(QString text);
    void setEventTypeIndex(int index);
    int getEventTypeIndex();
    void setRunning(bool isRunning);

signals:
    void startClicked();
    void stopClicked();

public slots:
    void handleActivation();
    void handleStartClicked();
    void handleStopClicked();
};

#endif // CHECKINOUTVIEW_H
