#include "checkinoutview.h"

CheckInOutView::CheckInOutView(MainWindow* dView, QObject* parent) : View(dView, parent)
{
}

QString CheckInOutView::url()
{
#if defined(MEEGO_VERSION)
    return "qrc:/qml/qml/BabyFeedMeego/CheckInOutPage.qml";
#else
    return "qrc:/qml/qml/BabyFeedSymbian/CheckInOutPage.qml";
#endif
}

QString CheckInOutView::viewName()
{
    return "checkInOutScreen";
}

void CheckInOutView::handleActivation()
{
    connect(mainItem(), SIGNAL(canceled()), this, SLOT(handleEventCanceled()));
    connect(mainItem(), SIGNAL(startStopClicked()), this, SLOT(handleStartStopClicked()));
    connect(mainItem(), SIGNAL(leftFeedClicked()), this, SLOT(handleLeftFeedClicked()));
    connect(mainItem(), SIGNAL(bottleClicked()), this, SLOT(handleBottleClicked()));
    connect(mainItem(), SIGNAL(rightFeedClicked()), this, SLOT(handleRightFeedClicked()));
    connect(mainItem(), SIGNAL(endFeeds()), this, SLOT(handleEndEvents()));
}

void CheckInOutView::handleEventCanceled()
{
    emit eventCanceled();
}

void CheckInOutView::setTotalTimerText(QString text)
{
    mainItem()->setProperty("totalTimerText", text);
}

void CheckInOutView::setParcialTimerText(QString text)
{
    mainItem()->setProperty("parcialTimerText", text);
}

void CheckInOutView::handleStartStopClicked()
{
    emit startStopClicked();
}

void CheckInOutView::handleLeftFeedClicked()
{
    emit leftFeedClicked();
}

void CheckInOutView::handleBottleClicked()
{
    emit bottleClicked();
}

void CheckInOutView::handleRightFeedClicked()
{
    emit rightFeedClicked();
}

void CheckInOutView::handleEndEvents()
{
    emit endEvents();
}

