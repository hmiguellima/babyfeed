#ifndef CALWRAPPER_H
#define CALWRAPPER_H

#include <QDateTime>
#include <QString>

class CalWrapper
{
public:
    CalWrapper();

    static QString setAlarm(QDateTime start, QDateTime end, QString message);
    static void removeAlarm(QString key, QDate date);
};

#endif // CALWRAPPER_H
