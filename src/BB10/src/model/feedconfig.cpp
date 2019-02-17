#include <QtSql/QSqlQuery>
#include <QVariant>
#include "feedconfig.h"

FeedConfig *FeedConfig::instance=0;

FeedConfig *FeedConfig::getInstance() {
    if (!instance)
        instance=new FeedConfig();

    return instance;
}

FeedConfig::FeedConfig()
{
    QSqlQuery query;

    query.exec("select fcfg_timeBetween, fcfg_alertActive, fcfg_notfActive, fcfg_version from FeedConfig");

    while (query.next())
    {
        timeBetween=query.value(0).toInt();
        alertActive=query.value(1).toBool();
        notfActive=query.value(2).toBool();
        version=query.value(3).toString();
    }
}

int FeedConfig::getTimeBetween()
{
    return timeBetween;
}

bool FeedConfig::isAlertActive()
{
    return alertActive;
}

bool FeedConfig::isNotfActive()
{
    return notfActive;
}

QString FeedConfig::getVersion()
{
    return version;
}
