#include "nobaby.h"
#include <QApplication>
#include <QImage>

NoBaby::NoBaby() : Baby()
{
    data->gender=NewBaby;
    data->id=-1;
    data->selected=false;
    data->name=QApplication::tr("<New baby>");
}

QString NoBaby::getAge()
{
    return "";
}

QString NoBaby::getLastMeasures()
{
    return "";
}