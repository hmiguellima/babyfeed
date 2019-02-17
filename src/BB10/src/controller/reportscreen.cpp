#include "reportscreen.h"
#include "global.h"
#include <QDate>
#include <QDateTime>
#include "model/eventbus.h"
#include "../BabyFeedApp.hpp"
#include "model/event.h"
#include <QList>
#include <math.h>
#include <QLocale>
#include <QFile>
#include <QDir>

ReportScreen::ReportScreen(BabyFeedApp* window) : Screen(window)
{
    view=new ReportsView(window, this);
    setView(view);

    connect(EventBus::getInstance(), SIGNAL(showReportScreen(Baby&)), this, SLOT(showReport(Baby&)));
    connect(view, SIGNAL(htmlLoaded(int)), this, SLOT(handleHtmlLoaded(int)));
}

ReportScreen::~ReportScreen()
{
}

void ReportScreen::showReport(Baby &baby) {
	this->baby=baby;
    show();
}

void ReportScreen::viewReadyHandler()
{
    view->setTitle(baby.getName()+tr("'s Charts"));
    if (baby.getGender()==Boy)
    	view->setGender("boy");
    else
    	view->setGender("girl");
}

void ReportScreen::handleHtmlLoaded(int index) {
    QList<PEvent> eventList;
	float babyValues[37];
	QDate startDate;
	QDate endDate;
	PEvent event;
	QString data="\"baby\"";
    int monthSpan;
    int count=0;
    int totalEvents=0;
    float value;

    startDate=baby.getMinMeasurementEventDate();
    endDate=baby.getMaxMeasurementEventDate();
    eventList=baby.listMeasureEvents(startDate, endDate);

    for (int i=0;i<37;i++)
    	babyValues[i]=0;

    foreach(event, eventList)
    {
        monthSpan=(event->getStartDate().date().year()-baby.getBirthDate().date().year())*12+(event->getStartDate().date().month()-baby.getBirthDate().date().month());
        switch (index) {
        case 0:
            babyValues[monthSpan]=(double)event->getHeight()/100;
        	break;
        case 1:
            babyValues[monthSpan]=(double)event->getWeight()/100;
        	break;
        case 2:
            babyValues[monthSpan]=(double)event->getCephalic()/100;
        	break;
        }

        totalEvents++;
    }

	for (int i=0;i<37;i++) {
		value=babyValues[i];

		if (value==0)
			data+=",\"\"";
		else
			data+=QString(",%1").arg(value);
    }

    view->setChartData(data);
}

