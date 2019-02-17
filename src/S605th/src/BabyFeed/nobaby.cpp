#include "nobaby.h"
#include <QApplication>

NoBaby::NoBaby() : Baby()
{
    data->gender=NewBaby;
    data->id=-1;
    data->selected=false;
}

QIcon NoBaby::getFoto()
{
    QIcon icon(QString::fromUtf8(":/icons/icons/new_baby_icon.jpg"));
    return icon;
}

QString NoBaby::getName()
{
    return QApplication::tr("<New baby>");
}
