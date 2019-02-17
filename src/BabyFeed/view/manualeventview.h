#ifndef MANUALEVENTVIEW_H
#define MANUALEVENTVIEW_H

#include "view/view.h"
#include "mainwindow.h"
#include <QDate>
#include <QTime>

class ManualEventView : public View
{
    Q_OBJECT
public:
    ManualEventView(MainWindow* dView, QObject* parent);

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
    void eventCanceled();
    void save();

public slots:
    void handleActivation();

private slots:
    void handleEventCanceled();
    void handleSave();
};


#endif // MANUALEVENTVIEW_H
