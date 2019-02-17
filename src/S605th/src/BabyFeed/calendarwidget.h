#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QDate>

namespace Ui {
    class CalendarWidget;
}

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = 0);
    ~CalendarWidget();

    void setSelectedDate(QDate date);
    QDate getSelectedDate();

signals:
    void selectionChanged();

private:
    Ui::CalendarWidget *ui;

private slots:
    void showPrevMonth();
    void showNextMonth();
    void updateAnoMesLabel(int ano, int mes);
    void emitSelectionChanged();
};

#endif // CALENDARWIDGET_H
