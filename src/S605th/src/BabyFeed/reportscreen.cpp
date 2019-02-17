#include "reportscreen.h"

#include <QLayout>
#include <QLabel>
#include <QPainter>
#include <QDate>
#include <QDateTime>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include "qwt/qwt_plot_layout.h"
#include "qwt/qwt_plot_curve.h"
#include "qwt/qwt_scale_draw.h"
#include "qwt/qwt_scale_widget.h"
#include "qwt/qwt_legend.h"
#include "qwt/qwt_legend_item.h"
#include "eventbus.h"
#include <QSizePolicy>
#include "mainwindow.h"
#include "event.h"
#include <QList>
#include <math.h>

class TimeScaleDraw: public QwtScaleDraw
{
public:
    TimeScaleDraw(const QDate &base):
        baseTime(base)
    {
    }
    virtual QwtText label(double v) const
    {
        QDate upTime = baseTime.addDays((int)v);
        return upTime.toString("MMM/dd");
    }
private:
    QDate baseTime;
};


class BabyCurve: public QwtPlotCurve
{
public:
    BabyCurve(const QString &title):
        QwtPlotCurve(title)
    {
        setRenderHint(QwtPlotItem::RenderAntialiased);
    }

    void setColor(const QColor &color)
    {
        QColor c = color;
        c.setAlpha(150);

        setPen(c);
        setBrush(c);
    }
};

void BabyPlot::showCurve(QwtPlotItem *item, bool on)
{
    item->setVisible(on);
    QWidget *w = legend()->find(item);
    if ( w && w->inherits("QwtLegendItem") )
        ((QwtLegendItem *)w)->setChecked(on);

    replot();
}

BabyPlot::BabyPlot(QWidget *parent):
    QwtPlot(parent)
{
    QwtScaleWidget *scaleWidget;
    BabyCurve *curve;

    setAutoReplot(false);

    plotLayout()->setAlignCanvasToScales(true);

    QwtLegend *legend = new QwtLegend;
    legend->setItemMode(QwtLegend::CheckableItem);
    legend->setFont(QFont("MS Shell Dlg 2", 6));
    insertLegend(legend, QwtPlot::TopLegend);

    setAxisLabelRotation(QwtPlot::xBottom, -50.0);
    setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

    scaleWidget = axisWidget(QwtPlot::xBottom);
    scaleWidget->setFont(QFont("MS Shell Dlg 2", 6));
    const int fmh = QFontMetrics(scaleWidget->font()).height();
    scaleWidget->setMinBorderDist(0, fmh / 2);

    setAxisScale(QwtPlot::yLeft, 0, 24);

    scaleWidget = axisWidget(QwtPlot::yLeft);
    scaleWidget->setFont(QFont("MS Shell Dlg 2", 6));


    curve = new BabyCurve(tr("Day feeds"));
    curve->setPen(QPen(Qt::red));
    curve->attach(this);
    data[DayTimeFeeds].curve = curve;

    curve = new BabyCurve(tr("Night feeds"));
    curve->setPen(QPen(Qt::blue));
    curve->attach(this);
    data[NightTimeFeeds].curve = curve;

    curve = new BabyCurve(tr("Max Interval(hrs)"));
    curve->setPen(QPen(Qt::green));
    curve->attach(this);
    data[MaxTimeBetweenFeeds].curve = curve;

    connect(this, SIGNAL(legendChecked(QwtPlotItem *, bool)),
        SLOT(showCurve(QwtPlotItem *, bool)));
}

void BabyPlot::setBabyData(Baby &baby, int daySpan)
{
    QList<PEvent> eventList;
    PEvent event;
    int dayTime=0;
    int nightTime=0;
    int timeBetween=0;
    QDateTime lastTime;
    QDate date;
    int day;
    int deltaHours;
    int eventCount;
    bool lastTimeInited=false;
    PEvent firstEvent;

    setAxisScaleDraw(QwtPlot::xBottom,
                     new TimeScaleDraw(QDate::currentDate().addDays(-(daySpan-1))));
    setAxisScale(QwtPlot::xBottom, 0, daySpan-1);

    timeData.clear();
    data[DayTimeFeeds].data.clear();
    data[NightTimeFeeds].data.clear();
    data[MaxTimeBetweenFeeds].data.clear();

    for (day=daySpan-1;day>=0;day--)
    {
        date=QDate::currentDate().addDays(-day);
        eventList=baby.listEvents(date, date);
        dayTime=0;
        nightTime=0;
        timeBetween=0;
        eventCount=eventList.count();

        // Existe sempre pelo menos um evento nem que seja o vazio
        // temos que ter isso em conta

        if (!lastTimeInited)
        {
            firstEvent=eventList.at(eventCount-1);
            if (!firstEvent->isEmpty())
            {
                lastTime=firstEvent->getStartDate();
                lastTimeInited=true;
            }
        }

        for (int index=eventCount-1;index>=0;index--)
        {
            event=eventList.at(index);
            if ( (event->getType()=='M') || (event->isEmpty()) )
                continue;


            if ( (event->getStartDate().time()>QTime(8,0)) && (event->getStartDate().time()<QTime(22,0)) )
                dayTime++;
            else
                nightTime++;

            deltaHours=abs((int)(lastTime.secsTo(event->getStartDate())/3600));
            // ignorar mais do que 8 horas de distancia entre alimentações
            if ( (deltaHours>timeBetween) && (deltaHours<9) )
                timeBetween=deltaHours;

            lastTime=event->getStartDate();
        }

        timeData << (daySpan-1)-day;
        data[DayTimeFeeds].data << dayTime;
        data[NightTimeFeeds].data << nightTime;
        data[MaxTimeBetweenFeeds].data << timeBetween;
    }


    data[DayTimeFeeds].curve->setSamples(timeData, data[DayTimeFeeds].data);
    data[NightTimeFeeds].curve->setSamples(timeData, data[NightTimeFeeds].data);
    data[MaxTimeBetweenFeeds].curve->setSamples(timeData, data[MaxTimeBetweenFeeds].data);

    showCurve(data[DayTimeFeeds].curve, true);
    showCurve(data[NightTimeFeeds].curve, true);
    showCurve(data[MaxTimeBetweenFeeds].curve, true);
}


ReportScreen::ReportScreen(MainWindow* window) : Screen(window)
{
    QVBoxLayout *topLayout=new QVBoxLayout(this);
    QScrollArea *scrollArea=new QScrollArea();
    QWidget *mainPanel=new QWidget();
    QVBoxLayout *mainLayout=new QVBoxLayout(mainPanel);
    plot = new BabyPlot(scrollArea);

    topLayout->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(mainPanel);
    mainLayout->addWidget(plot);
    plot->setMargin(0);

    connect(EventBus::getInstance(), SIGNAL(showReportScreen(Baby&)), this, SLOT(showReport(Baby&)));
    addAction(getWindow()->getBackAction());
}

ReportScreen::~ReportScreen()
{

}

void ReportScreen::showHandler()
{
}

void ReportScreen::showReport(Baby &baby) {
    getWindow()->setWindowTitle(tr("%0's Feedings Report").arg(baby.getName()));
    plot->setBabyData(baby, 15);
    show();
}

void ReportScreen::goBack()
{
    EventBus::getInstance()->fireShowMainScreen();
}
