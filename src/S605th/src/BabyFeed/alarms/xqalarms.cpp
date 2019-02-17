#include "xqalarms.h"
#include "xqalarms_p.h"

#include <QTime>

/*!
    \class XQAlarms
    \brief The XQAlarms class can be used to set, remove and modifying alarms
*/

/*!
    Constructs an XQAlarms object with the given parent.
    
    Call error() to get a value of XQAlarms::Error that indicates if an error
    occurred during construction.
    \sa error()
*/
XQAlarms::XQAlarms(QObject *parent) : QObject(parent),
    d(new XQAlarmsPrivate(this))
{
}

/*!
    Destroys the XQAlarms object.
*/
XQAlarms::~XQAlarms()
{
    delete d;
}

/*!
    \enum XQAlarms::Error
    
    This enum defines the possible errors for a XQAlarms object.
*/
/*! \var XQAlarms::Error XQAlarms::NoError
    No error occured.
*/
/*! \var XQAlarms::Error XQAlarms::OutOfMemoryError
    Not enough memory.
*/
/*! \var XQAlarms::Error XQAlarms::NotFoundError
    Not enough memory.
*/
/*! \var XQAlarms::Error XQAlarms::CouldNotConnectError
    Not enough memory.
*/
/*! \var XQAlarms::Error XQAlarms::AccessDeniedError
    Not enough memory.
*/
/*! \var XQAlarms::Error XQAlarms::UnknownError
    Unknown error.
*/

/*!
    Gets the alarm specified by the alarmId
        
    \param alarmId Alarm's id
    \return XQAlarm object
    \sa alarmIds
*/
XQAlarm XQAlarms::alarm(int alarmId) const
{
    return d->alarm(alarmId);
}

/*!
    This function returns the list of Alarm Id list.
    
    Note: Function may occur an error. Call error() to get the
    XQAlarms::Error value that indicates which error occurred
    
    \return List of alarm ids
    \sa error()
*/
QList<int> XQAlarms::alarmIds() const
{
    return d->alarmIds();
}

/*!
    This sets an alarm. If the XQAlarm cataegory is not set, the alarm category is set to
    KClockAlarm. On return, alarm gets an unique identifier to identify the alarm.
    
    \param alarmData An XQAlarm object
    \return If false is returned, an error has occurred. Call error() to get the
    XQAlarms::Error value that indicates which error occurred
    \sa deleteAlarm(), error()
*/
bool XQAlarms::addAlarm(XQAlarm& alarmData)
{
    return d->addAlarm(alarmData);
}


/*!
    This sets an alarm to be enabled or disabled.
    
	\param alarmId The id of the alarm to enable or disable
    \param status Sets the alarm's next due time.
    \return If false is returned, an error has occurred. Call error() to get the
    XQAlarms::Error value that indicates which error occurred
    \sa isEnabled(), error()
*/
bool XQAlarms::setEnabled(int alarmId, bool status)
{
    return d->setEnabled(alarmId, status);
}

/*!
    
    \param alarmId Alarm id to find the status of
	\return  True if the alarm is enabled, otherwise false.

	
    \sa setEnabled()
*/
bool XQAlarms::isEnabled(int alarmId) const
{
    return d->isEnabled(alarmId);
}

/*!
    Removes the alarm with given id.
    
    \param alarmId Alarm to be removed
    \return If false is returned, an error has occurred. Call error() to get the
    XQAlarms::Error value that indicates which error occurred
    \sa addAlarm(), error()
*/
bool XQAlarms::deleteAlarm(int alarmId)
{
    return d->deleteAlarm(alarmId);
}

/*!
    
    \return The type of error that occurred when the last function call failed, otherwise returns NoError.
*/
XQAlarms::Error XQAlarms::error() const
{
    return d->error();
}


/*!
    \class XQAlarms
    \brief The XQAlarm class stores alarm data. If category is not set, default
    value is clock alarm
*/    
/*!
    Constructs a XQAlarm object.
*/
XQAlarm::XQAlarm() : m_id(-1), m_category(-1)
{
}

/*!
    Destroys the XQAlarm object.
*/
XQAlarm::~XQAlarm()
{
}

/*!
    \enum XQAlarm::RepeatDefinition

    This enum defines the possible repeat definitions for the XQAlarm object.
*/
/*! \var XQAlarm::RepeatDefinition XQAlarm::RepeatOnce
    Repeating alarm once.
*/
/*! \var XQAlarm::RepeatDefinition XQAlarm::RepeatNext24Hours
    Repeating alarm in next 24 hours.
*/
/*! \var XQAlarm::RepeatDefinition XQAlarm::RepeatDaily
    Repeating alarm daily.
*/
/*! \var XQAlarm::RepeatDefinition XQAlarm::RepeatWorkdays
    Repeating alarm workdays.
*/
/*! \var XQAlarm::RepeatDefinition XQAlarm::RepeatWeekly
    Repeating alarm weekly in some weekday.
*/

/*!
    This function gets the alarm id.
    
    \return The alarm id
*/
int XQAlarm::id() const
{
    return m_id;
}

/*!
    Sets the alarm message. The maximum message length is 128 characters.
    
    \param message Sets the message that is shown when alarm comes
    \sa message(), addAlarm()
*/
void XQAlarm::setMessage(const QString& message)
{
    m_message = message;
}

/*!
    \return The message associated with the alarm.
    
    \sa setMessage(), addAlarm()
*/
QString XQAlarm::message() const
{
    return m_message;
}

/*!
    Sets the expiry time of the alarm.
    
    \param expiryTime Sets the alarm's original expiry time.
    \sa nextDueTime(), addAlarm()
*/
void XQAlarm::setExpiryTime(const QDateTime& expiryTime)
{
    m_expiryTime = expiryTime;
}

/*!
    
    \return The original expiry time of the alarm.
    \sa setExpiryTime(), addAlarm()
*/
QDateTime XQAlarm::expiryTime() const
{
    return m_expiryTime;
}

/*!
    
    \return  The next due time for the alarm. The original expiry time is returned if the alarm is not snoozed,
	otherwise the snooze time is returned.
.
    \sa setNextDueTime(), addAlarm()
*/
QDateTime XQAlarm::nextDueTime() const
{
    return m_nextDueTime;
}

/*!
    This function sets the alarm category.
    
    \param category The alarm category
    \sa category(), addAlarm()
*/
void XQAlarm::setCategory(int category)
{
    m_category = category;
}

/*!
    This function gets the alarm category
    
    \return The alarm category
    \sa setCategory(), addAlarm()
*/
int XQAlarm::category() const
{
    return m_category;
}

/*!
    This sets alarm repeat definition
    
    \param repeatDefinition The alarm repeat definition
    \sa repeatDefinition(), addAlarm()
*/
void XQAlarm::setRepeatDefinition(XQAlarm::RepeatDefinition repeatDefinition)
{
    m_repeatDefinition = repeatDefinition;
}

/*!
    This function gets the alarm category
    
    \return The alarm category
    \sa setRepeatDefinition(), addAlarm()
*/
XQAlarm::RepeatDefinition XQAlarm::repeatDefinition() const
{
    return m_repeatDefinition;
}
