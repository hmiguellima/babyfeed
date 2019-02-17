#ifndef REPORTSCREEN_H
#define REPORTSCREEN_H

#include "screen.h"
#include "model/baby.h"
#include <QVector>
#include "view/reportsview.h"
#include <QStringList>

class ReportScreen : public Screen
{
    Q_OBJECT

public:
    ReportScreen(BabyFeedApp* window);
    ~ReportScreen();

public slots:
    void viewReadyHandler();

private:
    ReportsView* view;
    Baby baby;

private slots:
    void showReport(Baby &baby);
    void handleHtmlLoaded(int index);
};

#endif // REPORTSCREEN_H
