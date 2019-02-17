#ifndef MANUALEVENTVIEW_H
#define MANUALEVENTVIEW_H

#include "view/view.h"
#include "../BabyFeedApp.hpp"
#include <QDate>
#include <QTime>

class ManualEventView : public View
{
    Q_OBJECT
public:
    ManualEventView(BabyFeedApp* dView, QObject* parent);

    QString url();
    QString viewName();

    void setEventTypeIndex(int index);
    int getEventTypeIndex();
    void setStartDate(QDate date);
    QDate getStartDate();
    void setStartTime(QTime time);
    QTime getStartTime();
    void setDuration(int duration);
    int getDuration();
    void setGeneralNotes(QString notes);
    QString getGeneralNotes();
    void setMedicineName(QString name);
    QString getMedicineName();
    void setMedicineNotes(QString notes);
    QString getMedicineNotes();

    void setWeight(int weight);
    int getWeight();
    void setHeight(int height);
    int getHeight();
    void setCephalic(int cephalic);
    int getCephalic();

    void setInterval(int hours);
    int getInterval();
    void setEndDate(QDate date);
    QDate getEndDate();
    void setStartDateEnabled(bool enabled);
    void setStartTimeEnabled(bool enabled);
    void setEventTypeBtnRowEnabled(bool enabled);
    void setRecurrenceVisible(bool visible);

signals:
    void save();
    void deleteEvent();

public slots:
    void handleActivation();

private slots:
    void handleSave();
    void handleDelete();
};


#endif // MANUALEVENTVIEW_H
