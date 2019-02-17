#include "calendarwidget.h"
#include "ui_calendarwidget.h"

CalendarWidget::CalendarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalendarWidget)
{
    ui->setupUi(this);
    connect(ui->prevMonthBtn, SIGNAL(clicked()), this, SLOT(showPrevMonth()));
    connect(ui->nextMonthBtn, SIGNAL(clicked()), this, SLOT(showNextMonth()));
    connect(ui->calendarWidget, SIGNAL(currentPageChanged(int,int)), this, SLOT(updateAnoMesLabel(int,int)));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(emitSelectionChanged()));

    setSelectedDate(QDate::currentDate());
    updateAnoMesLabel(QDate::currentDate().year(), QDate::currentDate().month());
}

CalendarWidget::~CalendarWidget()
{
    delete ui;
}

void CalendarWidget::setSelectedDate(QDate date)
{
    ui->calendarWidget->setSelectedDate(date);
}

QDate CalendarWidget::getSelectedDate()
{
    return ui->calendarWidget->selectedDate();
}

void CalendarWidget::showNextMonth()
{
    ui->calendarWidget->showNextMonth();
}

void CalendarWidget::showPrevMonth()
{
    ui->calendarWidget->showPreviousMonth();
}

void CalendarWidget::updateAnoMesLabel(int ano, int mes)
{
    ui->mesAnoLabel->setText(QDate(ano, mes, 1).toString("MMM, yyyy"));
}

void CalendarWidget::emitSelectionChanged()
{
    emit selectionChanged();
}
