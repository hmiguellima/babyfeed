#include "reportscreen.h"
#include "global.h"
#include <QLayout>
#include <QLabel>
#include <QPainter>
#include <QDate>
#include <QDateTime>
#include <QVBoxLayout>
#include "qwt/qwt_plot_layout.h"
#include "qwt/qwt_plot_curve.h"
#include "qwt/qwt_scale_draw.h"
#include "qwt/qwt_scale_widget.h"
#include "qwt/qwt_legend.h"
#include "qwt/qwt_legend_item.h"
#include "model/eventbus.h"
#include <QSizePolicy>
#include "mainwindow.h"
#include "model/event.h"
#include <QList>
#include <math.h>
#include <QLocale>
#include <QApplication>
#include <QImage>
#include <QDeclarativeContext>
#include <QFile>
#include <QDir>

#define MAX_Y 18
#define FONT_NAME "Nokia Pure"
#if defined(MEEGO_VERSION)
    #define REPORT_WIDTH 480
    #define REPORT_HEIGHT 650
    #define FONT_SIZE 12
#else
    #define FONT_SIZE 6
    #define REPORT_WIDTH 360
    #define REPORT_HEIGHT 463
#endif

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
        return QLocale().toString(upTime, "MMM/dd");
    }
private:
    QDate baseTime;
};

class MonthScaleDraw: public QwtScaleDraw
{
public:
    MonthScaleDraw(const QDate &base):
        baseTime(base)
    {
    }
    virtual QwtText label(double v) const
    {
        QDate upTime = baseTime.addMonths((int)v);
        return QLocale().toString(upTime, "MMM/yyyy");
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

    /*
    void setColor(const QColor &color)
    {
        QColor c = color;
        c.setAlpha(150);

        setPen(c);
        setBrush(c);
        setPen(color);
    }
    */
};

void FeedingsPlot::showCurve(QwtPlotItem *item, bool on)
{
    item->setVisible(on);
    QWidget *w = legend()->find(item);
    if ( w && w->inherits("QwtLegendItem") )
        ((QwtLegendItem *)w)->setChecked(on);

    replot();
}

FeedingsPlot::FeedingsPlot(QWidget *parent):
    QwtPlot(parent)
{
    QwtScaleWidget *scaleWidget;
    BabyCurve *curve;
    QPen pen;
    QPalette pal=palette();

    setAutoReplot(false);
    plotLayout()->setAlignCanvasToScales(true);
    setAutoFillBackground(true);
    pal.setColor(QPalette::Window, QColor::fromRgb(255,255,255));
    pal.setColor(QPalette::Text, QColor::fromRgb(0,0,0));
    pal.setColor(QPalette::Foreground, QColor::fromRgb(0,0,0));
    pal.setColor(QPalette::ButtonText, QColor::fromRgb(0,0,0));
    setPalette(pal);


    QwtLegend *legend = new QwtLegend;
    pal=legend->palette();
    pal.setColor(QPalette::Text, QColor::fromRgb(0,0,0));
    legend->setPalette(pal);
    legend->setItemMode(QwtLegend::ReadOnlyItem);
    legend->setFont(QFont(FONT_NAME, FONT_SIZE));
    insertLegend(legend, QwtPlot::TopLegend);

    scaleWidget = axisWidget(QwtPlot::xBottom);
    scaleWidget->setFont(QFont(FONT_NAME, FONT_SIZE));
    const int fmh = QFontMetrics(scaleWidget->font()).height();
    scaleWidget->setMinBorderDist(0, fmh / 2);

    setAxisAutoScale(QwtPlot::yLeft);

    scaleWidget = axisWidget(QwtPlot::yLeft);
    scaleWidget->setFont(QFont(FONT_NAME, FONT_SIZE));


    curve = new BabyCurve(tr("Day feeds"));
    pen=QPen(Qt::red);
    pen.setWidth(2);
    pen.setStyle(Qt::DashLine);
    curve->setPen(pen);
    curve->attach(this);
    data[DayTimeFeeds].curve = curve;

    curve = new BabyCurve(tr("Night feeds"));
    pen=QPen(Qt::blue);
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    curve->setPen(pen);
    curve->attach(this);
    data[NightTimeFeeds].curve = curve;

    curve = new BabyCurve(tr("Max Int hrs"));
    pen=QPen(Qt::darkGreen);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    curve->setPen(pen);
    curve->attach(this);
    data[MaxTimeBetweenFeeds].curve = curve;

    curve = new BabyCurve(tr("Avg feed min"));
    pen=QPen(Qt::gray);
    pen.setWidth(2);
    pen.setStyle(Qt::DashDotDotLine);
    curve->setPen(pen);
    curve->attach(this);
    data[AverageFeedTime].curve = curve;

    //connect(this, SIGNAL(legendChecked(QwtPlotItem *, bool)),
    //    SLOT(showCurve(QwtPlotItem *, bool)));
}

void FeedingsPlot::setBabyData(Baby &baby, int daySpan)
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
    int totalFeedTime;
    int totalFeeds;
    QDate startDate;
    QDate endDate;
    QString teste;


    startDate=baby.getMinFeedEventDate();
    teste=startDate.toString();
    endDate=baby.getMaxFeedEventDate();
    teste=startDate.toString();

    if (endDate>QDate::currentDate())
        endDate=QDate::currentDate();

    if (endDate.addDays(-(daySpan-1))<startDate)
        endDate=startDate.addDays(daySpan-1);

    setAxisScaleDraw(QwtPlot::xBottom,
                     new TimeScaleDraw(endDate.addDays(-(daySpan-1))));
    setAxisScale(QwtPlot::xBottom, 0, daySpan-1);
    setAxisLabelRotation(QwtPlot::xBottom, -90.0);
    setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

    timeData.clear();
    data[DayTimeFeeds].data.clear();
    data[NightTimeFeeds].data.clear();
    data[MaxTimeBetweenFeeds].data.clear();
    data[AverageFeedTime].data.clear();

    for (day=daySpan-1;day>=0;day--)
    {
        date=endDate.addDays(-day);
        teste=date.toString();
        eventList=baby.listFeedEvents(date, date);
        dayTime=0;
        nightTime=0;
        timeBetween=0;
        totalFeedTime=0;
        totalFeeds=0;
        eventCount=eventList.count();

        for (int index=eventCount-1;index>=0;index--)
        {
            event=eventList.at(index);
            if (event->isEmpty())
                continue;

            if (!lastTimeInited)
            {
                lastTime=event->getStartDate();
                lastTimeInited=true;
            }

            if ( (event->getStartDate().time()>QTime(8,0)) && (event->getStartDate().time()<QTime(22,0)) )
                dayTime++;
            else
                nightTime++;

            deltaHours=abs((int)(lastTime.secsTo(event->getStartDate())/3600));
            // ignorar mais do que MAX_Y horas de distancia entre alimentações
            if (deltaHours>timeBetween)
            {
                if (deltaHours<=MAX_Y)
                    timeBetween=deltaHours;
                else
                    timeBetween=MAX_Y;
            }

            totalFeedTime+=event->getDuration();
            totalFeeds++;

            lastTime=event->getStartDate();
        }

        if (timeBetween==0)
            timeBetween=MAX_Y;

        timeData << (daySpan-1)-day;
        data[DayTimeFeeds].data << dayTime;
        data[NightTimeFeeds].data << nightTime;
        data[MaxTimeBetweenFeeds].data << timeBetween;
        if (totalFeeds>0)
            data[AverageFeedTime].data << (int)(totalFeedTime/(totalFeeds));
        else
            data[AverageFeedTime].data << 0;
    }


    data[DayTimeFeeds].curve->setSamples(timeData, data[DayTimeFeeds].data);
    data[NightTimeFeeds].curve->setSamples(timeData, data[NightTimeFeeds].data);
    data[MaxTimeBetweenFeeds].curve->setSamples(timeData, data[MaxTimeBetweenFeeds].data);
    data[AverageFeedTime].curve->setSamples(timeData, data[AverageFeedTime].data);

    showCurve(data[DayTimeFeeds].curve, true);
    showCurve(data[NightTimeFeeds].curve, true);
    showCurve(data[MaxTimeBetweenFeeds].curve, true);
    showCurve(data[AverageFeedTime].curve, true);
}

void MeasurePlot::showCurve(QwtPlotItem *item, bool on)
{
    item->setVisible(on);
    QWidget *w = legend()->find(item);
    if ( w && w->inherits("QwtLegendItem") )
        ((QwtLegendItem *)w)->setChecked(on);

    replot();
}

MeasurePlot::MeasurePlot(QWidget *parent, QColor color, QString measureLabel):
    QwtPlot(parent)
{
    QwtScaleWidget *scaleWidget;
    BabyCurve *curve;
    QPen pen;
    QPalette pal;

    setAutoReplot(false);
    plotLayout()->setAlignCanvasToScales(true);
    setAutoFillBackground(true);
    pal.setColor(QPalette::Window, QColor::fromRgb(255,255,255));
    pal.setColor(QPalette::Text, QColor::fromRgb(0,0,0));
    pal.setColor(QPalette::Foreground, QColor::fromRgb(0,0,0));
    pal.setColor(QPalette::ButtonText, QColor::fromRgb(0,0,0));
    setPalette(pal);


    QwtLegend *legend = new QwtLegend;
    pal=legend->palette();
    pal.setColor(QPalette::Text, QColor::fromRgb(0,0,0));
    legend->setPalette(pal);
    legend->setItemMode(QwtLegend::ReadOnlyItem);
    legend->setFont(QFont(FONT_NAME, FONT_SIZE));
    insertLegend(legend, QwtPlot::TopLegend);

    scaleWidget = axisWidget(QwtPlot::xBottom);
    scaleWidget->setFont(QFont(FONT_NAME, FONT_SIZE));
    const int fmh = QFontMetrics(scaleWidget->font()).height();
    scaleWidget->setMinBorderDist(0, fmh / 2);

    setAxisAutoScale(QwtPlot::yLeft);

    scaleWidget = axisWidget(QwtPlot::yLeft);
    scaleWidget->setFont(QFont(FONT_NAME, FONT_SIZE));


    curve = new BabyCurve(measureLabel);
    pen=QPen(color);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    curve->setPen(pen);
    curve->attach(this);
    data[Measure].curve = curve;

    connect(this, SIGNAL(legendChecked(QwtPlotItem *, bool)),
        SLOT(showCurve(QwtPlotItem *, bool)));
}

void MeasurePlot::setBabyData(QList<PEvent> eventList, QDate startDate, QDate endDate)
{
    PEvent event;
    int monthSpan;
    int eventCount=0;
    double lastMeasure=0;

    monthSpan=(endDate.year()-startDate.year())*12+(endDate.month()-startDate.month())+1;

    setAxisScaleDraw(QwtPlot::xBottom,
                     new MonthScaleDraw(QDate(startDate.year(), startDate.month(), 1)));
    setAxisAutoScale(QwtPlot::xBottom);
    //setAxisScale(QwtPlot::xBottom, 0, monthSpan-1, 1);
    setAxisLabelRotation(QwtPlot::xBottom, -90.0);
    setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

    data[Measure].data.clear();
    data[Measure].timeData.clear();

    foreach(event,eventList)
    {
        if (event->isEmpty())
            continue;

        if (getMeasure(event)!=0)
        {
            eventCount++;
            monthSpan=(event->getStartDate().date().year()-startDate.year())*12+(event->getStartDate().date().month()-startDate.month());
            lastMeasure = getMeasure(event);
            data[Measure].timeData << monthSpan;
            data[Measure].data << lastMeasure;
        }
    }

    if (eventCount<=1)
    {
        setAxisScale(QwtPlot::xBottom, 0, 1, 1);
        data[Measure].timeData << 0;
        data[Measure].data << lastMeasure;
        data[Measure].timeData << 1;
        data[Measure].data << lastMeasure;
    }


    data[Measure].curve->setSamples(data[Measure].timeData, data[Measure].data);
    showCurve(data[Measure].curve, true);
}


WeightMeasurePlot::WeightMeasurePlot(QWidget *parent):
    MeasurePlot(parent, Qt::red, QApplication::tr("Weight"))
{
}

double WeightMeasurePlot::getMeasure(PEvent event)
{
    return (double)event->getWeight()/100;
}

HeightMeasurePlot::HeightMeasurePlot(QWidget *parent):
    MeasurePlot(parent, Qt::blue, QApplication::tr("Height"))
{
}

double HeightMeasurePlot::getMeasure(PEvent event)
{
    return (double)event->getHeight()/100;
}

CephalicMeasurePlot::CephalicMeasurePlot(QWidget *parent):
    MeasurePlot(parent, Qt::darkGreen, QApplication::tr("Cephalic Perimeter"))
{
}

double CephalicMeasurePlot::getMeasure(PEvent event)
{
    return (double)event->getCephalic()/100;
}

ReportScreen::ReportScreen(MainWindow* window) : Screen(window)
{
    view=new ReportsView(window, this);
    setView(view);

    // Feedings graph
    feedPlot = new FeedingsPlot();
    feedPlot->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    feedPlot->setFixedSize(REPORT_WIDTH, REPORT_HEIGHT);


    // Weight graph
    weightMeasurePlot = new WeightMeasurePlot(this);
    weightMeasurePlot->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    weightMeasurePlot->setFixedSize(REPORT_WIDTH, REPORT_HEIGHT);

    // Height graph
    heightMeasurePlot = new HeightMeasurePlot(this);
    heightMeasurePlot->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    heightMeasurePlot->setFixedSize(REPORT_WIDTH, REPORT_HEIGHT);

    // Cephalic graph
    cephalicMeasurePlot = new CephalicMeasurePlot(this);
    cephalicMeasurePlot->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cephalicMeasurePlot->setFixedSize(REPORT_WIDTH, REPORT_HEIGHT);

    connect(EventBus::getInstance(), SIGNAL(showReportScreen(Baby&)), this, SLOT(showReport(Baby&)));
    connect(view, SIGNAL(backClicked()), this, SLOT(goBack()));
    connect(view, SIGNAL(reportIndexChanged(int)), this, SLOT(handleReportIndexChanged(int)));
}


ReportScreen::~ReportScreen()
{
}

void ReportScreen::showReport(Baby &baby) {
    QDate startDate;
    QDate endDate;
    QList<PEvent> eventList;
    QImage reportImage;
    QString reportUri;
    QStringList filters;
    QString path;
    QStringList oldReportFiles;

    this->baby=baby;
    //updateTitle();

    filters << "bfreport*.png";
    reportUriList.clear();
    path=appDataPath;
    oldReportFiles=QDir(appDataPath).entryList(filters);
    foreach(reportUri, oldReportFiles) {
        QFile(appDataPath+"/"+reportUri).remove();
    }

    feedPlot->setBabyData(baby, 15);
    feedPlot->setMargin(5);

    reportImage=QImage(REPORT_WIDTH, REPORT_HEIGHT, QImage::Format_RGB32);
    feedPlot->render(&reportImage);
    reportUri=appDataPath+"/bfreportf_"+QString::number((int)(rand()%1000))+".png";
    reportImage.save(reportUri);
#if defined(MEEGO_VERSION)
    reportUriList.append("file://"+reportUri);
#else
    reportUriList.append("file:///"+reportUri);
#endif

    startDate=baby.getMinMeasurementEventDate();
    endDate=baby.getMaxMeasurementEventDate();
    eventList=baby.listMeasureEvents(startDate, endDate);

    weightMeasurePlot->setBabyData(eventList, startDate, endDate);
    weightMeasurePlot->setMargin(5);

    reportImage=QImage(REPORT_WIDTH, REPORT_HEIGHT, QImage::Format_RGB32);
    weightMeasurePlot->render(&reportImage);
    reportUri=appDataPath+"/bfreportw_"+QString::number((int)(rand()%1000))+".png";
    reportImage.save(reportUri);
#if defined(MEEGO_VERSION)
    reportUriList.append("file://"+reportUri);
#else
    reportUriList.append("file:///"+reportUri);
#endif

    heightMeasurePlot->setBabyData(eventList, startDate, endDate);
    heightMeasurePlot->setMargin(5);

    reportImage=QImage(REPORT_WIDTH, REPORT_HEIGHT, QImage::Format_RGB32);
    heightMeasurePlot->render(&reportImage);
    reportUri=appDataPath+"/bfreporth_"+QString::number((int)(rand()%1000))+".png";
    reportImage.save(reportUri);
#if defined(MEEGO_VERSION)
    reportUriList.append("file://"+reportUri);
#else
    reportUriList.append("file:///"+reportUri);
#endif

    cephalicMeasurePlot->setBabyData(eventList, startDate, endDate);
    cephalicMeasurePlot->setMargin(5);

    reportImage=QImage(REPORT_WIDTH, REPORT_HEIGHT, QImage::Format_RGB32);
    cephalicMeasurePlot->render(&reportImage);
    reportUri=appDataPath+"/bfreportc_"+QString::number((int)(rand()%1000))+".png";
    reportImage.save(reportUri);
#if defined(MEEGO_VERSION)
    reportUriList.append("file://"+reportUri);
#else
    reportUriList.append("file:///"+reportUri);
#endif
    getWindow()->rootContext()->setContextProperty("reportsModel", reportUriList);

    show();
}


void ReportScreen::goBack()
{
    EventBus::getInstance()->fireShowMainScreen();
}

void ReportScreen::viewReadyHandler()
{
    handleReportIndexChanged(0);
}

void ReportScreen::handleReportIndexChanged(int index)
{
    QString title;

    switch (index)
    {
    case 0:
        title=tr("%0's Feedings Report").arg(baby.getName());
        break;
    case 1:
        title=tr("%0's Weight Report").arg(baby.getName());
        break;
    case 2:
        title=tr("%0's Height Report").arg(baby.getName());
        break;
    case 3:
        title=tr("%0's Cephalic Report").arg(baby.getName());
        break;
    default:
        title="";
    }

    setTitle(title);
}
