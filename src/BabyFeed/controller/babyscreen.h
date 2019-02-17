#ifndef BABYSCREEN_H
#define BABYSCREEN_H

#include "screen.h"
#include "model/baby.h"
#include <QByteArray>
#include <QImage>
#include "model/contactsmodel.h"
#include "model/notification.h"
#include "view/babyview.h"

class BabyScreen : public Screen
{
    Q_OBJECT

public:
    explicit BabyScreen(MainWindow* window);
    ~BabyScreen();

public slots:
    void viewReadyHandler();

private:
    Baby baby;
    ContactsModel *contactsModel;
    bool photoCaptured;
    BabyView* view;

private slots:
    void onShowBabyScreen(Baby &baby);
    void saveBaby();
    void handleNotificationChange(int index, QString type);
    void handleContactsLoaded();
};

#endif // BABYSCREEN_H
