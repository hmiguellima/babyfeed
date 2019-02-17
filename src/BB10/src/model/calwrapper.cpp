#include "calwrapper.h"
#include <QSharedPointer>
#include <QLatin1String>
#include <QDebug>
#include <bb/pim/calendar/CalendarService>
#include <bb/pim/calendar/CalendarEvent>

using namespace bb::pim::calendar;

CalWrapper::CalWrapper()
{
}

QString CalWrapper::setAlarm(QDateTime start, QDateTime end, QString message)
{
	CalendarService service;
	CalendarEvent event;

	event.setStartTime(start);
	event.setEndTime(end);
	event.setSensitivity(Sensitivity::Personal);
	event.setAccountId(1);
	event.setFolderId(1);
	event.setSubject(message);
	event.setReminder(1);

	service.createEvent(event);

	return QString("%1").arg(event.id());
}

void CalWrapper::removeAlarm(QString key, QDate date)
{
	CalendarService service;
	CalendarEvent event;
	Result::Type result;

	event=service.event(1, QVariant(key).toInt(), &result);

	if (result==Result::Success)
		service.deleteEvent(event);
}
