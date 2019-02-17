#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QByteArray>
#include <QImage>
#include "baby.h"
#include "event.h"

class EventBus : public QObject
{
    Q_OBJECT
public:
    EventBus();
    ~EventBus();

    void fireEventAdded(PEvent &event);
    void fireEventDeleted(PEvent &event);
    void fireBabyAdded(Baby &baby);
    void fireBabyDeleted(Baby &baby);
    void fireShowBabyScreen(Baby &baby);
    void fireShowCheckInOutScreen(Baby &baby);
    void fireShowManualEventScreen(Baby &baby);
    void fireShowOptionsScreen();
    void fireShowMainScreen();
    void fireShowCameraScreen();
    void fireBabyPhotoCaptured(QByteArray data);
    void fireBabyPhotoAborted();
    void fireBabySelected(Baby &baby);
    void fireBabyUpdated(Baby &baby);
    void fireDataReset();
    void fireShowEventInfo(PEvent &event);
    void fireEventUpdated(PEvent &event);
    void fireShowReportScreen(Baby &baby);

    static EventBus* getInstance() {
        return instance;
    }

private:
    static EventBus *instance;

signals:
    void eventAdded(PEvent &event);
    void eventDeleted(PEvent &event);
    void babyAdded(Baby &baby);
    void babyDeleted(Baby &baby);
    void showMainScreen();
    void showBabyScreen(Baby &baby);
    void showCheckInOutScreen(Baby &baby);
    void showManualEventScreen(Baby &baby);
    void showOptionsScreen();
    void showCameraScreen();
    void babyPhotoCaptured(QByteArray data);
    void babyPhotoAborted();
    void babySelected(Baby &baby);
    void babyUpdated(Baby &baby);
    void dataReset();
    void showEventInfo(PEvent &event);
    void eventUpdated(PEvent &event);
    void showReportScreen(Baby &baby);
};

#endif // EVENTBUS_H
