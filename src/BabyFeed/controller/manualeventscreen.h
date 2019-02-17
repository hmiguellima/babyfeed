#ifndef MANUALEVENTSCREEN_H
#define MANUALEVENTSCREEN_H

#include "screen.h"
#include "model/baby.h"
#include "model/event.h"
#include "view/manualeventview.h"
#include "model/contactsmodel.h"

class ManualEventScreen : public Screen
{
    Q_OBJECT

public:
    explicit ManualEventScreen(MainWindow* window);
    ~ManualEventScreen();

public slots:
    void viewReadyHandler();

private:
    ManualEventView* view;
    Baby baby;
    PEvent event;
    ContactsModel* contactsModel;

    bool edit;
    void cleanNotes();

private slots:
    void onShowManualEventScreen(Baby &baby);
    void onShowEventInfo(PEvent &event);
    void save();
    void testAlarm();
};

#endif // MANUALEVENTSCREEN_H
