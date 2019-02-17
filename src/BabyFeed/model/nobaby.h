#ifndef NOBABY_H
#define NOBABY_H

#include <QString>
#include <QIcon>
#include "baby.h"

class NoBaby : public Baby
{
public:
    NoBaby();
    QString getAge();
    QString getLastMeasures();
};

#endif // NOBABY_H
