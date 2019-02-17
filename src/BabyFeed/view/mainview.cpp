#include "mainview.h"
#include <QUrl>
#include <QDeclarativeContext>
#include <QGraphicsObject>
#include <QList>
#include <QVariant>
#include <QDate>

MainView::MainView(MainWindow* dView, QObject* parent) : View(dView, parent)
{
    _babiesModel=new BabiesModel(this);
    _eventModel=new EventModel(this);

    dView->rootContext()->setContextProperty("babiesModel", _babiesModel);
    dView->rootContext()->setContextProperty("eventsModel", _eventModel);
}

void MainView::setEventsList(QList<PEvent > *events)
{
    _eventModel->setEvents(*events);
}

void MainView::setBabyList(QList<Baby> *babies)
{
    _babiesModel->setBabies(babies);
}

void MainView::setSelectedBaby(int index)
{
}

void MainView::setEventsDate(QString date)
{
    mainItem()->setProperty("setDateBtnText", QVariant(date));
}

QString MainView::url()
{
#if defined(MEEGO_VERSION)
    return "qrc:/qml/qml/BabyFeedMeego/MainPage.qml";
#else
    return "qrc:/qml/qml/BabyFeedSymbian/MainPage.qml";
#endif
}

QString MainView::viewName()
{
    return "mainScreen";
}

void MainView::handleBabyChanged(int index)
{
    qDebug("c++:MainView::handleBabyChanged");
    emit babyChanged(index);
}

void MainView::handleActivation()
{
    connect(mainItem(), SIGNAL(babyIndexChanged(int)), this, SLOT(handleBabyChanged(int)));
    connect(mainItem(), SIGNAL(prevDateClicked()), this, SLOT(handlePrevDateClicked()));
    connect(mainItem(), SIGNAL(nextDateClicked()), this, SLOT(handleNextDateClicked()));
    connect(mainItem(), SIGNAL(dateChanged(int, int, int)), this, SLOT(handleDateChanged(int,int,int)));
    connect(mainItem(), SIGNAL(uncheckEventClicked(int)), this, SLOT(handleUncheckEventClicked(int)));
    connect(mainItem(), SIGNAL(checkEventClicked(int)), this, SLOT(handleCheckEventClicked(int)));
    connect(mainItem(), SIGNAL(editEventClicked(int)), this, SLOT(handleEditEventClicked(int)));
    connect(mainItem(), SIGNAL(deleteEventClicked(int)), this, SLOT(handleDeleteEventClicked(int)));
    connect(mainItem(), SIGNAL(timerEventClicked()), this, SLOT(handleTimerEventClicked()));
    connect(mainItem(), SIGNAL(manualEventClicked()), this, SLOT(handleManualEventClicked()));
    connect(mainItem(), SIGNAL(reportClicked()), this, SLOT(handleReportClicked()));
    connect(mainItem(), SIGNAL(editBabyClicked(int)), this, SLOT(handleEditBaby(int)));
    connect(mainItem(), SIGNAL(deleteBabyClicked(int)), this, SLOT(handleDeleteBaby(int)));
    connect(mainItem(), SIGNAL(newBabyClicked()), this, SLOT(handleNewBaby()));
}

void MainView::refreshBaby(int index)
{
    _babiesModel->refresh();
}

void MainView::handlePrevDateClicked()
{
    emit prevDayBtnClicked();
}

void MainView::handleNextDateClicked()
{
    emit nextDayBtnClicked();
}

void MainView::handleDateChanged(int year, int month, int day)
{
    emit dateSelected(QDate(year, month,day));
}

void MainView::handleCheckEventClicked(int index)
{
    emit checkEventClicked(index);
}

void MainView::handleUncheckEventClicked(int index)
{
    emit uncheckEventClicked(index);
}

void MainView::handleEditEventClicked(int index)
{
    emit editEventClicked(index);
}

void MainView::handleDeleteEventClicked(int index)
{
    emit deleteEventClicked(index);
}

void MainView::handleTimerEventClicked()
{
    emit timerBtnClicked();
}

void MainView::handleManualEventClicked()
{
    emit eventBtnClicked();
}

void MainView::handleReportClicked()
{
    emit reportBtnClicked();
}

void MainView::handleEditBaby(int index)
{
    emit editBabyClicked(index);
}

void MainView::handleDeleteBaby(int index)
{
    emit deleteBabyClicked(index);
}

void MainView::handleNewBaby()
{
    emit newBabyClicked();
}

void MainView::setCurrentBabyIndex(int index)
{
    QMetaObject::invokeMethod(mainItem(), "positionBabyToIndex", Q_ARG(QVariant, index));
}

