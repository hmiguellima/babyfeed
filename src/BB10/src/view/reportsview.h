#ifndef REPORTSVIEW_H
#define REPORTSVIEW_H

#include "view/view.h"
#include "../BabyFeedApp.hpp"
#include <QStringList>

class ReportsView : public View
{
    Q_OBJECT
public:
    ReportsView(BabyFeedApp* dView, QObject* parent);

    QString url();
    QString viewName();

    void setChartData(QString data);
    void setGender(QString gender);

signals:
	void htmlLoaded(int index);

public slots:
    void handleActivation();
    void handleHtmlLoaded(int index);
};

#endif // REPORTSVIEW_H
