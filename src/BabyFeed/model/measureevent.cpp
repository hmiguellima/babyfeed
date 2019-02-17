#include "measureevent.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QString>
#include <QMessageBox>
#include <QList>

const QString MeasureEvent::ICON="weight";

MeasureEvent::MeasureEvent()
{
    setType(Event::TYPE_MEASURE);
    validator=new QDoubleValidator(this);
    validator->setRange(0, 9999.99, 2);
    validator->setNotation(QDoubleValidator::StandardNotation);
}

QString MeasureEvent::getShortDesc()
{
    return QString("W:%0, H:%1, C:%2").
            arg((float)getWeight()/100).
            arg((float)getHeight()/100).
            arg((float)getCephalic()/100);
}

QString MeasureEvent::getAlarmDesc()
{
    return "";
}

QString MeasureEvent::getNotfDesc()
{
    return "";
}

QString MeasureEvent::getIcon()
{
    return ICON;
}

PEvent MeasureEvent::clone()
{
    PEvent event=PEvent(new MeasureEvent());

    event->setWeight(getWeight());
    event->setHeight(getHeight());
    event->setCephalic(getCephalic());

    return event;
}

bool MeasureEvent::isRecurrentAble()
{
    return false;
}

QString MeasureEvent::getLastMeasures(Baby &baby)
{
    QDate startDate;
    QDate endDate;
    QList<PEvent> measuresList;
    PEvent event;
    QString weight="--";
    QString height="--";
    QString cephalic="--";

    startDate=baby.getMinMeasurementEventDate();
    endDate=baby.getMaxMeasurementEventDate();
    measuresList=baby.getLastMeasureEvent();

    if (measuresList.size()>0)
    {
        event=measuresList[0];
        if (event->getWeight()>0)
            weight=QString::number((float)event->getWeight()/100);
        if (event->getHeight()>0)
            height=QString::number((float)event->getHeight()/100);
        if (event->getCephalic()>0)
            cephalic=QString::number((float)event->getCephalic()/100);
    }

    return QApplication::tr("W:%0, H:%1, C:%2").
            arg(weight).
            arg(height).
            arg(cephalic);
}
