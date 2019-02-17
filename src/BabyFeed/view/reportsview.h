#ifndef REPORTSVIEW_H
#define REPORTSVIEW_H

#include "view/view.h"
#include "mainwindow.h"
#include <QStringList>

class ReportsView : public View
{
    Q_OBJECT
public:
    ReportsView(MainWindow* dView, QObject* parent);

    QString url();
    QString viewName();

signals:
    void backClicked();
    void reportIndexChanged(int index);

public slots:
    void handleActivation();
    void handleReportIndexChanged(int index);
    void handleBack();
};

#endif // REPORTSVIEW_H
