#include "reportsview.h"

ReportsView::ReportsView(MainWindow* dView, QObject* parent) : View(dView, parent)
{
}

QString ReportsView::url()
{
#if defined(MEEGO_VERSION)
    return "qrc:/qml/qml/BabyFeedMeego/ReportsPage.qml";
#else
    return "qrc:/qml/qml/BabyFeedSymbian/ReportsPage.qml";
#endif
}

QString ReportsView::viewName()
{
    return "reportsScreen";
}

void ReportsView::handleActivation()
{
    connect(mainItem(), SIGNAL(back()), this, SLOT(handleBack()));
    connect(mainItem(), SIGNAL(reportIndexChanged(int)), this, SLOT(handleReportIndexChanged(int)));
}

void ReportsView::handleBack()
{
    emit backClicked();
}

void ReportsView::handleReportIndexChanged(int index)
{
    emit reportIndexChanged(index);
}
