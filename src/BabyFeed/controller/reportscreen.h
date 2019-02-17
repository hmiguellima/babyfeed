#ifndef REPORTSCREEN_H
#define REPORTSCREEN_H

#include "screen.h"
#include "qwt/qwt_plot.h"
#include "model/baby.h"
#include <QVector>
#include <QWidget>
#include "view/reportsview.h"
#include <QStringList>

class QwtPlotCurve;
class MainWindow;

class FeedingsPlot : public QwtPlot
{
    Q_OBJECT
public:
    enum BabyData
    {
        DayTimeFeeds,
        NightTimeFeeds,
        MaxTimeBetweenFeeds,
        AverageFeedTime
    };

    FeedingsPlot(QWidget * = 0);
    const QwtPlotCurve *babyCurve(int id) const
        { return data[id].curve; }

    void setBabyData(Baby &baby, int daySpan);

private Q_SLOTS:
    void showCurve(QwtPlotItem *, bool on);

private:
    struct
    {
        QwtPlotCurve *curve;
        QVector<double> data;
    } data[AverageFeedTime+1];
    QVector<double> timeData;
};

class MeasurePlot : public QwtPlot
{
    Q_OBJECT
public:
    enum BabyData
    {
        Measure
    };

    MeasurePlot(QWidget *parent, QColor color, QString measureLabel);
    const QwtPlotCurve *babyCurve(int id) const
        { return data[id].curve; }

    void setBabyData(QList<PEvent> eventList, QDate startDate, QDate endDate);
    virtual double getMeasure(PEvent event)=0;

protected Q_SLOTS:
    void showCurve(QwtPlotItem *, bool on);

protected:
    struct
    {
        QwtPlotCurve *curve;
        QVector<double> data;
        QVector<double> timeData;
    } data[Measure+1];
};

class WeightMeasurePlot : public MeasurePlot
{
    Q_OBJECT
public:
    WeightMeasurePlot(QWidget *parent);
    double getMeasure(PEvent event);
};

class HeightMeasurePlot : public MeasurePlot
{
    Q_OBJECT
public:
    HeightMeasurePlot(QWidget *parent);
    double getMeasure(PEvent event);
};

class CephalicMeasurePlot : public MeasurePlot
{
    Q_OBJECT
public:
    CephalicMeasurePlot(QWidget *parent);
    double getMeasure(PEvent event);
};

class ReportScreen : public Screen
{
    Q_OBJECT

public:
    ReportScreen(MainWindow* window);
    ~ReportScreen();

public slots:
    void viewReadyHandler();

private:
    ReportsView* view;
    FeedingsPlot* feedPlot;
    WeightMeasurePlot* weightMeasurePlot;
    HeightMeasurePlot* heightMeasurePlot;
    CephalicMeasurePlot* cephalicMeasurePlot;
    Baby baby;
    QStringList reportUriList;

private slots:
    void showReport(Baby &baby);
    void goBack();
    void handleReportIndexChanged(int index);
};

#endif // REPORTSCREEN_H
