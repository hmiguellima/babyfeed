#ifndef MANUALEVENTSCREEN_H
#define MANUALEVENTSCREEN_H

#include "screen.h"
#include "flickable/qscrollareakineticscroller.h"
#include "baby.h"
#include "event.h"
#include <QAction>

namespace Ui {
    class ManualEventScreen;
}

class ManualEventScreen : public Screen
{
    Q_OBJECT

public:
    explicit ManualEventScreen(MainWindow* window);
    ~ManualEventScreen();

protected:
    void showHandler();

private:
    Ui::ManualEventScreen *ui;
    QScrollAreaKineticScroller kineticScroller;
    Baby baby;
    PEvent event;
    bool edit;
    QAction *saveAction;

private slots:
    void onShowManualEventScreen(Baby &baby);
    void onShowEventInfo(PEvent &event);
    void save();
    void updateEndDate();
    void updateNotesStack(char type);
};

#endif // MANUALEVENTSCREEN_H
