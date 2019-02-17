#ifndef BABYSCREEN_H
#define BABYSCREEN_H

#include <QWidget>
#include "screen.h"
#include "flickable/qscrollareakineticscroller.h"
#include "baby.h"
#include <QAction>
#include <QMenu>
#include <QByteArray>
#include <QImage>
#include "contactsmodel.h"
#include <QComboBox>
#include "notification.h"

namespace Ui {
    class BabyScreen;
}

class BabyScreen : public Screen
{
    Q_OBJECT

public:
    explicit BabyScreen(MainWindow* window);
    ~BabyScreen();

protected:
    virtual void showHandler();

private:
    Ui::BabyScreen *ui;
    QScrollAreaKineticScroller kineticScroller1;
    QScrollAreaKineticScroller kineticScroller2;
    QAction *saveAction;
    Baby baby;
    ContactsModel *contactsModel;
    QComboBox *notfMenu;

private slots:
    void onShowBabyScreen(Baby &baby);
    void onBabyPhotoCaptured(QByteArray data);
    void onBabyPhotoAborted();
    void saveBaby();
    void deleteBaby();
    void takePhoto();
    void showNotfMenu(QModelIndex index);
    void changeNotification(int notfType);
};

#endif // BABYSCREEN_H
