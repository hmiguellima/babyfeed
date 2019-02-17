#include "datepickerdialog.h"
#include <QVBoxLayout>
#include <QAction>

DatePickerDialog::DatePickerDialog(QDate date, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *vLayout=new QVBoxLayout(this);
    QAction *todayAction=new QAction(tr("Today"), this);
    QAction *cancelAction=new QAction(tr("Cancel"), this);

    calendar=new CalendarWidget();
    calendar->setSelectedDate(date);

    vLayout->addWidget(calendar);
    setLayout(vLayout);

    todayAction->setSoftKeyRole(QAction::PositiveSoftKey);
    cancelAction->setSoftKeyRole(QAction::NegativeSoftKey);
    addAction(todayAction);
    addAction(cancelAction);

    connect(todayAction, SIGNAL(triggered()), this, SLOT(selectToday()));
    connect(cancelAction, SIGNAL(triggered()), this, SLOT(reject()));
    connect(calendar, SIGNAL(selectionChanged()), this, SLOT(accept()));
}

QDate DatePickerDialog::getSelectedDate()
{
    return calendar->getSelectedDate();
}

void DatePickerDialog::selectToday()
{
    calendar->setSelectedDate(QDate::currentDate());
}
