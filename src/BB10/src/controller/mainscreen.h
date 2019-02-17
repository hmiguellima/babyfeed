#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "screen.h"
#include <QAbstractListModel>
#include <QModelIndex>
#include "model/baby.h"
#include "model/nobaby.h"
#include <QHash>
#include <QDate>
#include "view/mainview.h"

class BabyFeedApp;

class MainScreen : public Screen
{
    Q_OBJECT

public:
    MainScreen(BabyFeedApp* window);
    ~MainScreen();

public slots:
    void viewReadyHandler();

private:
    MainView* view;
    QList<Baby> babies;
    NoBaby noBaby;

private slots:
    void handleShowBabyPage(int babyId);
    void handleDeleteBaby(int babyId);
    void updateMainView();
};

#endif // MAINSCREEN_H
