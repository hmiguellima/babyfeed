#include "nobaby.h"

NoBaby::NoBaby() : Baby()
{
    data->gender=NewBaby;
    data->id=-1;
    data->selected=false;
    data->name=QObject::tr("<New baby>");
}

QString NoBaby::getAge()
{
    return "";
}

QString NoBaby::getLastMeasures()
{
    return "";
}
