#include "reportsview.h"

ReportsView::ReportsView(BabyFeedApp* dView, QObject* parent) : View(dView, parent)
{
}

QString ReportsView::url()
{
	return "reports";
}

QString ReportsView::viewName()
{
    return "reportScreen";
}

void ReportsView::handleActivation()
{
	connect(mainItem(), SIGNAL(htmlLoaded(int)), this, SLOT(handleHtmlLoaded(int)));
}

void ReportsView::setChartData(QString data) {
	QMetaObject::invokeMethod(mainItem(), "setChartData", Q_ARG(QVariant, QVariant(QString("var babyValues=[%1]").arg(data))));
}

void ReportsView::setGender(QString gender) {
    mainItem()->setProperty("gender", QVariant(gender));
}

void ReportsView::handleHtmlLoaded(int index) {
	emit htmlLoaded(index);
}
