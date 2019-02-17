#ifndef NOBABY_H
#define NOBABY_H

#include <QString>
#include <QIcon>
#include "baby.h"

class NoBaby : public Baby
{
public:
    NoBaby();
    virtual QIcon getFoto();
    virtual QString getName();
private:
};

#endif // NOBABY_H
