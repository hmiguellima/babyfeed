#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include "screen.h"
#include "eventmodel.h"
#include "event.h"
#include <QAbstractListModel>
#include <QModelIndex>
#include <QMessageBox>
#include "expandedlistview.h"
#include <QAction>
#include "baby.h"
#include "babyicon.h"
#include <QMap>
#include "kineticscrollarea.h"
#include "flickable/qscrollareakineticscroller.h"
#include <QDate>
#include <QComboBox>

namespace Ui {
    class MainScreen;
}

class MainWindow;

class MainScreen : public Screen
{
    Q_OBJECT

public:
    explicit MainScreen(MainWindow* window);
    ~MainScreen();

signals:
    void babyListBuilt();

protected:
    void showHandler();

private:
    Ui::MainScreen *ui;
    QScrollAreaKineticScroller kineticScroller1;
    QScrollAreaKineticScroller kineticScroller2;
    EventModel model;
    BabyIcon *selectedBabyIcon;
    QMap<int,BabyIcon*> iconMap;
    KineticScrollArea *scroller;
    QDate date;
    QComboBox *eventMenu;

    void toogleButtons(bool enable);
    void updateWindowTitle();
    void clearBabySelection();
    void updateCurrentDateLabel();

private slots:
    void buildBabyListView();
    void babySelected(Baby &baby);
    void babyAdded(Baby &baby);
    void babyUpdated(Baby &baby);
    void babyDeleted(Baby &baby);
    void showCheckInOutScreen();
    void showManualEventScreen();
    void updateEventModelAndShow(PEvent &event);
    void showEventInfo(PEvent &event);
    void showNextDay();
    void showPrevDay();
    void showEventMenu(QModelIndex index);
    void handleEventMenuActivated(int index);
    void removeEventRow(int row);
    void showReportScreen();
    void scrollToSelectedBaby();
};

#endif // MAINSCREEN_H
