#ifndef MANUALEVENTSCREEN_H
#define MANUALEVENTSCREEN_H

#include "screen.h"
#include "model/baby.h"
#include "model/event.h"
#include "view/manualeventview.h"

class ManualEventScreen : public Screen
{
    Q_OBJECT

public:
    explicit ManualEventScreen(BabyFeedApp* window);
    ~ManualEventScreen();

public slots:
    void viewReadyHandler();

private:
    ManualEventView* view;
    Baby baby;
    PEvent event;

    bool edit;
    void cleanNotes();

private slots:
    void onShowManualEventScreen(Baby &baby);
    void onShowEventInfo(PEvent &event);
    void save();
    void deleteEvent();
    void testAlarm();
};

#endif // MANUALEVENTSCREEN_H
