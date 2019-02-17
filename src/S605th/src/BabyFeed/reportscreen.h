#ifndef REPORTSCREEN_H
#define REPORTSCREEN_H

#include "screen.h"
#include "qwt/qwt_plot.h"
#include "baby.h"
#include <QVector>



class QwtPlotCurve;
class MainWindow;

class BabyPlot : public QwtPlot
{
    Q_OBJECT
public:
    enum BabyData
    {
        DayTimeFeeds,
        NightTimeFeeds,
        MaxTimeBetweenFeeds
    };

    BabyPlot(QWidget * = 0);
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
    } data[MaxTimeBetweenFeeds+1];
    QVector<double> timeData;
};


class ReportScreen : public Screen
{
    Q_OBJECT

public:
    ReportScreen(MainWindow* window);
    ~ReportScreen();

protected:
    virtual void showHandler();

private:
    BabyPlot *plot;

private slots:
    void showReport(Baby &baby);
    void goBack();
};

#endif // REPORTSCREEN_H
