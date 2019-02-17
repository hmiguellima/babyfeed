#include "manualeventscreen.h"
#include "ui_manualeventscreen.h"
#include "mainwindow.h"
#include "eventbus.h"
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QTextEdit>
#include "feedingevent.h"
#include "medicineevent.h"

ManualEventScreen::ManualEventScreen(MainWindow *window) :
    Screen(window),
    ui(new Ui::ManualEventScreen)
{
    ui->setupUi(this);

    kineticScroller.setWidget(ui->scrollArea_2);

    saveAction=new QAction(tr("Save"), this);
    saveAction->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(saveAction);
    addAction(getWindow()->getBackAction());

    connect(EventBus::getInstance(), SIGNAL(showManualEventScreen(Baby&)), this, SLOT(onShowManualEventScreen(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(showEventInfo(PEvent&)), this, SLOT(onShowEventInfo(PEvent&)));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->startCalendar, SIGNAL(selectionChanged()), this, SLOT(updateEndDate()));
    connect(ui->eventPanel, SIGNAL(eventSelected(char)), this, SLOT(updateNotesStack(char)));

    edit=false;
}

ManualEventScreen::~ManualEventScreen()
{
    delete ui;
}

void ManualEventScreen::showHandler()
{
    getWindow()->setWindowTitle(baby.getName()+tr("'s Event"));
}

void ManualEventScreen::onShowManualEventScreen(Baby &baby)
{
    QDate dataAgora=QDate::currentDate();
    QTime horaAgora=QTime::currentTime();

    if (edit)
        ui->tabWidget->addTab(ui->scheduleTab, tr("Schedule"));
    edit=false;
    this->baby=baby;
    ui->startCalendar->setSelectedDate(dataAgora);
    ui->tabWidget->setCurrentIndex(0);
    ui->durationBox->setValue(0);
    ui->timeEdit->setTime(horaAgora);
    ui->notesEdit->setPlainText("");
    ui->endCalendar->setSelectedDate(dataAgora);
    ui->repeatMinBox->setValue(0);
    ui->eventPanel->setType('L');
    ui->startCalendar->setEnabled(true);
    ui->timeEdit->setEnabled(true);
    ui->notesStack->setCurrentIndex(0);
    ui->drugEdit->setText("");
    ui->drugNotesEdit->setPlainText("");
    ui->eventPanel->setEnabled(true);

    show();
}

void ManualEventScreen::onShowEventInfo(PEvent &event)
{
    this->event=event;

    if (!edit)
        ui->tabWidget->removeTab(2);

    edit=true;
    ui->tabWidget->setCurrentIndex(0);
    ui->startCalendar->setSelectedDate(event->getStartDate().date());
    ui->timeEdit->setTime(event->getStartDate().time());
    ui->eventPanel->setType(event->getType());
    ui->eventPanel->setEnabled(false);
    ui->durationBox->setValue(event->getDuration());
    ui->startCalendar->setEnabled(false);
    ui->timeEdit->setEnabled(false);
    switch (event->getType())
    {
    case 'L':
    case 'B':
    case 'R':
        ui->notesStack->setCurrentIndex(0);
        ui->notesEdit->setPlainText(event->getNotes());
        break;
    default:
        ui->notesStack->setCurrentIndex(1);
        MedicineEvent *medEvent;
        medEvent=dynamic_cast<MedicineEvent*> (event.data());
        ui->drugNotesEdit->setPlainText(medEvent->getNotes());
        ui->drugEdit->setText(medEvent->getMedicineName());
    }

    show();
}

void ManualEventScreen::save()
{
    QString notes;
    char eventType;

    eventType=ui->eventPanel->getType();

    if (edit)
    {
        event->setDuration(ui->durationBox->value());
        event->setType(ui->eventPanel->getType());
        switch(eventType)
        {
        case 'L':
        case 'B':
        case 'R':
            notes=ui->notesEdit->toPlainText();
            break;
        default:
            MedicineEvent *medEvent;
            notes=ui->drugNotesEdit->toPlainText();
            QString medicineName=ui->drugEdit->text();
            medEvent=dynamic_cast<MedicineEvent*> (event.data());
            medEvent->setMedicineName(medicineName);
        }

        event->setNotes(notes);
        event->persist();

        EventBus::getInstance()->fireEventUpdated(event);
    }
    else
    {
        QDate startDate;
        QDate endDate;
        QTime startTime;
        QDateTime time;
        int repeatMin;
        int recurrenceId=-1;

        startDate=ui->startCalendar->getSelectedDate();
        endDate=ui->endCalendar->getSelectedDate();
        startTime=ui->timeEdit->time();
        repeatMin=ui->repeatMinBox->value();

        time=QDateTime(startDate, startTime);


        if (time.date()>endDate)
        {
            QMessageBox::information(this, tr("BabyFeed"), tr("The scheduled end date is inválid!"));
            return;
        }

        if ( (eventType=='M') && (ui->drugEdit->text().length()==0) )
        {
            QMessageBox::information(this, tr("BabyFeed"), tr("The medicine event requires a drug name!"));
            return;
        }

        if ((repeatMin>0)||(time.date()<endDate))
            recurrenceId=Event::getNextRecurrenceId();

        while (time.date()<=endDate)
        {
            switch (eventType)
            {
            case 'L':
            case 'B':
            case 'R':
                event=PEvent(new FeedingEvent());
                notes=ui->notesEdit->toPlainText();
                break;
            default:
                MedicineEvent *medEvent;
                notes=ui->drugNotesEdit->toPlainText();
                QString medicineName=ui->drugEdit->text();
                event=PEvent(medEvent=new MedicineEvent());
                medEvent->setMedicineName(medicineName);
            }
            event->setNotes(notes);
            event->setBabyId(baby.getId());
            event->setStartDate(time);
            event->setDuration(ui->durationBox->value());
            event->setType(eventType);
            event->setRecurrenceId(recurrenceId);
            if (time<=QDateTime::currentDateTime())
                event->setChecked(true);
            else
                event->setAlarm(time, event->getAlarmDesc());

            event->persist();

            if (repeatMin==0)
                time=time.addDays(1);
            else
                time=time.addSecs(repeatMin*60);
        }

        EventBus::getInstance()->fireEventAdded(event);
    }
}

void ManualEventScreen::updateEndDate()
{
    ui->endCalendar->setSelectedDate(ui->startCalendar->getSelectedDate());
}

void ManualEventScreen::updateNotesStack(char type)
{
    switch(type)
    {
    case 'L':
    case 'B':
    case 'R':
        ui->notesStack->setCurrentIndex(0);
        break;
    default:
        ui->notesStack->setCurrentIndex(1);
    }
}
