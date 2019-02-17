#include "xqcalendar.h"
#include "xqcalendar_p.h"

#include <QList>

/*!
    \class XQCalendar

    \brief The XQCalendar class can be used for managing calendar entries.
*/

/*!
    Constructs a XQCalendar object with the given parent.
*/
XQCalendar::XQCalendar(QObject* parent)
    : QObject(parent), d(new XQCalendarPrivate(this))
{
}

/*!
    Destroys the XQContacts object.
*/
XQCalendar::~XQCalendar()
{
    delete d;
}

/*!
    \enum XQCalendar::Error

    This enum defines the possible errors for a XQCalendar object.
*/
/*! \var XQCalendar::Error XQCalendar::NoError
    No error occured.
*/
/*! \var XQCalendar::Error XQCalendar::OutOfMemoryError
    Not enough memory.
*/
/*! \var XQCalendar::Error XQCalendar::AlreadyInUse
    Already in use
*/
/*! \var XQCalendar::Error XQCalendar::UnknownError
    Unknown error.
*/

/*!
    \enum XQCalendar::FilterFlags

    This enum defines the possible filters for a XQCalendar object.
*/
/*! \var XQCalendar::FilterFlags XQCalendar::IncludeAppointments
    Include timed appointments.
*/
/*! \var XQCalendar::FilterFlags XQCalendar::IncludeReminders
    Include appointments which only have a start time.
*/
/*! \var XQCalendar::FilterFlags XQCalendar::IncludeEvents
    Include all-day events.
*/
/*! \var XQCalendar::FilterFlags XQCalendar::IncludeAnniversaries
    Include anniversaries.
*/
/*! \var XQCalendar::FilterFlags XQCalendar::IncludeCompletedTodos
    Include completed todos.
*/
/*! \var XQCalendar::FilterFlags XQCalendar::IncludeIncompletedTodos
    Include incompleted todos.
*/
/*! \var XQCalendar::FilterFlags XQCalendar::IncludeAlarmedOnly
    Remove non-alarmed entries. This flag cannot be used by itself.
*/
/*! \var XQCalendar::FilterFlags XQCalendar::IncludeRptsNextInstanceOnly
    Include next only instance of a repeat entry.
*/
/*! \var XQCalendar::FilterFlags XQCalendar::IncludeAll
    Include all entries (appointments, day events, anniversaries and todos).
*/

/*!
    Adds new enty

    \param entry The entry to be added
    \return id of the added entry on success; otherwise returns 0.
    \sa deleteEntry(), updateEntry()
*/
ulong XQCalendar::addEntry(const XQCalendarEntry& entry)
{
    return d->addEntry(entry);
}

/*!
    Deletes the entry

    \param id The id of the entry to be deleted
    \return If false is returned, an error has occurred. Call error() to get a value of 
    XQCalendar::Error that indicates which error occurred
    \sa addEntry(), updateEntry()
*/
bool XQCalendar::deleteEntry(ulong id)
{
    return d->deleteEntry(id);
}

/*!
    Updates the entry

    \param entry The entry to be updated
    \return If false is returned, an error has occurred. Call error() to get a value of 
    XQCalendar::Error that indicates which error occurred
    \sa addEntry(), deleteEntry()
*/
bool XQCalendar::updateEntry(const XQCalendarEntry& entry)
{
    return d->updateEntry(entry);
}

/*!
    Fetches the entry which of id is equal to given \a id.

    \param id id of the entry to be returned
    \return the entry on success; null entry on failure
    \sa count()
*/
XQCalendarEntry XQCalendar::fetchById(ulong id)
{
    return d->fetchById(id);
}

/*!
    Tries to import calendar entries from the specified file.

    \param fileName The fully specified path and filename of the file from which vCalendars (calendar entries) will be imported
    \return Number of imported vCalendars (calendar entries)
    \sa exportAsvCalendar()
*/
int XQCalendar::importvCalendar(const QString& fileName)
{
    return d->importvCalendar(fileName);
}

/*!
    Exports the specified calendar entry to a file.

    \param fileName Fully specified path and filename of the file to export the vCalendar (calendar entry)  items into
    \param calendarEntryId Id of the calendar entry to be exported
    \return True if the calendar entry was successfully exported; otherwise returns false.
    \sa importvCalendar()
*/
bool XQCalendar::exportAsvCalendar(const QString& fileName, long int calendarEntryId)
{
    return d->exportAsvCalendar(fileName, calendarEntryId);
}

/*!
    Fetches all entry ids

    \param filters Filter flags specifying the types of entries to be returned
    \return the entry on success; null entry on failure
    \sa count()
*/
QList<ulong> XQCalendar::entryIds(XQCalendar::FilterFlags filter)
{
    return d->entryIds(filter);
}

/*!
    Returns the type of error that occurred if the latest function call failed; otherwise returns NoError.
    
    \return Error code
*/
XQCalendar::Error XQCalendar::error() const
{
    return d->error();
}

/*!
    \fn void XQMedia::entriesChanged(QList<ulong> ids)

    This signal is emitted when an entry or entries have changed.
    
    \param ids Ids of the entries
*/

// End of file
