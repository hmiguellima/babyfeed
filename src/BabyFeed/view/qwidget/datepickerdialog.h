#ifndef DATEPICKERDIALOG_H
#define DATEPICKERDIALOG_H

#include <QDialog>
#include <QDate>
#include "calendarwidget.h"

class DatePickerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DatePickerDialog(QDate date, QWidget *parent = 0);

    QDate getSelectedDate();
signals:

private slots:
    void selectToday();

private:
    CalendarWidget *calendar;
};

#endif // DATEPICKERDIALOG_H
