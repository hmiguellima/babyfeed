#ifndef BABYVIEW_H
#define BABYVIEW_H

#include "view/view.h"
#include "mainwindow.h"
#include "model/contactsmodel.h"

class BabyView : public View
{
    Q_OBJECT
public:
    BabyView(MainWindow* dView, QObject* parent);

    QString url();
    QString viewName();

    QString getPhotoUrl();
    void setPhotoUrl(QString url);
    QString getName();
    void setName(QString name);
    QDate getBirthday();
    void setBirthday(QDate birthday);
    int getGenderIndex();
    void setGenderIndex(int index);
    bool isTimerAlarmsActive();
    void setTimerAlarmsActive(bool active);
    int getTimerInterval();
    void setTimerInterval(int interval);
    void setNewBaby(bool isNew);
    bool isPhotoChanged();
    QString getCapturedDataPath();

signals:
    void canceled();
    void save();
    void notificationChanged(int index, QString type);

public slots:
    void handleActivation();

private slots:
    void handleCancel();
    void handleSave();
    void handleNotificationChanged(int index, QString type);
};

#endif // BABYVIEW_H
