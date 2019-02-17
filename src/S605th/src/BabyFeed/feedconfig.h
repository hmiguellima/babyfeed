#ifndef FEEDCONFIG_H
#define FEEDCONFIG_H

#include <QString>

class FeedConfig
{
public:
    static FeedConfig *getInstance();

    int getTimeBetween();
    bool isAlertActive();
    bool isNotfActive();
    QString getVersion();

private:
    static FeedConfig *instance;

    int timeBetween;
    bool alertActive;
    bool notfActive;
    QString version;

    FeedConfig();
};

#endif // FEEDCONFIG_H
