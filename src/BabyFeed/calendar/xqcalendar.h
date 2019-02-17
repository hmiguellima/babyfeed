#ifndef XQCALENDAR_H
#define XQCALENDAR_H

// INCLUDES
#include <QObject>
#include <QList>
#include "xqcalendarentry.h"
#include "calendar_global.h"

// FORWARD DECLARATIONS
class XQCalendarPrivate;

// CLASS DECLARATION
class XQCALENDAR_EXPORT XQCalendar : public QObject
{
    Q_OBJECT
    
public:

    enum Error {
        NoError = 0,
        OutOfMemoryError,
        AlreadyInUse,
        UnknownError = -1
    };
    
    enum FilterFlags
    {
        IncludeAppointments = 0x01,
        IncludeReminders = 0x02,
        IncludeEvents = 0x04,
        IncludeAnniversaries = 0x08,
        IncludeCompletedTodos = 0x10,
        IncludeIncompletedTodos = 0x20,
        IncludeAlarmedOnly = 0x40,
        IncludeRptsNextInstanceOnly = 0x80,
        IncludeAll=IncludeAppointments|IncludeReminders|IncludeEvents|IncludeAnniversaries|
        IncludeCompletedTodos|IncludeIncompletedTodos
    };

    XQCalendar(QObject* parent = 0);
    ~XQCalendar();
    
    ulong addEntry(const XQCalendarEntry& entry);
    bool deleteEntry(ulong id);
    bool updateEntry(const XQCalendarEntry& entry);
    QList<ulong> entryIds(XQCalendar::FilterFlags filter = XQCalendar::IncludeAll);
    XQCalendarEntry fetchById(ulong id);
    int importvCalendar(const QString& fileName);
    bool exportAsvCalendar(const QString& fileName, long int calendarEntryId);

    XQCalendar::Error error() const;
    
Q_SIGNALS:
    void entriesChanged(QList<ulong> ids);

private:
    friend class XQCalendarPrivate;
    XQCalendarPrivate* d;
};

#endif // XQCALENDAR_H

// End of file
