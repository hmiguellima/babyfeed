#include "xqcalendarentry.h"
#include "xqcalendarentry_p.h"

#include <calalarm.h>
#include <QDateTime>

/****************************************************
 *
 * XQCalendarAttendee
 *
 ****************************************************/

/*!
    \class XQCalendarAttendee

    \brief Class representing an attendee of an event.
           Contains the status and the role information of the attendee.
           Contains information about whether or not a response was requested for this attendee. 
           
*/

/*!
    \enum XQCalendarAttendee::ParticipantRole

    This enum defines the possible roles for a XQCalendarAttendee object 
    in case of entry's type is event.
*/
/*! \var XQCalendarAttendee::ParticipantRole XQCalendarAttendee::RequiredParticipant
    A required participant of the event.
*/
/*! \var XQCalendarAttendee::ParticipantRole XQCalendarAttendee::OptionalParticipant
    An optional participant of the event
*/
/*! \var XQCalendarAttendee::ParticipantRole XQCalendarAttendee::NonParticipant
    A non-participant of the event
*/
/*! \var XQCalendarAttendee::ParticipantRole XQCalendarAttendee::ChairParticipant
    This participant will chair the event
*/
/*! \var XQCalendarAttendee::ParticipantRole XQCalendarAttendee::ParticipantRoleUnknown
    The role is unknown
*/

/*!
    \enum XQCalendarAttendee::StatusType

    This enum defines the possible statuses for a XQCalendarAttendee object.
*/
/*! \var XQCalendarAttendee::StatusType XQCalendarAttendee::StatusNeedsAction
    Action is required by attendee
*/
/*! \var XQCalendarAttendee::StatusType XQCalendarAttendee::StatusAccepted
    Attendee has accepted request
*/
/*! \var XQCalendarAttendee::StatusType XQCalendarAttendee::StatusTentative
    Attendee has tentatively accepted the request
*/
/*! \var XQCalendarAttendee::StatusType XQCalendarAttendee::StatusConfirmed
    Attendee's presence is confirmed
*/
/*! \var XQCalendarAttendee::StatusType XQCalendarAttendee::StatusDeclined
    Attendee has declined request
*/
/*! \var XQCalendarAttendee::StatusType XQCalendarAttendee::StatusCompleted
    The required action has been completed by attendee
*/
/*! \var XQCalendarAttendee::StatusType XQCalendarAttendee::StatusDelegated
    Attendee has delegated the request to another person
*/
/*! \var XQCalendarAttendee::StatusType XQCalendarAttendee::StatusInProcess
    A to-do action in the process of being completed
*/
/*! \var XQCalendarAttendee::StatusType XQCalendarAttendee::StatusUnknown
    The status is unknown
*/

/*!
    Creates an attendee.
*/
XQCalendarAttendee::XQCalendarAttendee()
    : d(NULL)
{
}

/*!
    Constructs a new attendee using given \a address.

    \param address The address of the attendee
*/
XQCalendarAttendee::XQCalendarAttendee(const QString& address)
    : d(new XQCalendarAttendeePrivate)
{
    d->m_address = address;
    d->ref.ref();
}

/*!
    Destroys the attendee.
*/
XQCalendarAttendee::~XQCalendarAttendee()
{
    if (d && !d->ref.deref())
    {
        delete d;
    }
}

/*!
    Creates a copy of a given attendee.

    \param other attendee to be copied.
*/
XQCalendarAttendee::XQCalendarAttendee(const XQCalendarAttendee& other)
    : d(other.d)
{
    if (d) {
        d->ref.ref();
    }
}

/*!
    Sets the email address of the attendee.
    
    \param address The email address of the attendee 
    \sa address()
*/
void XQCalendarAttendee::setAddress(const QString& address)
{
    detach();
    d->m_address = address;
}

/*!
    Gets the email address of the attendee.
    
    \return The email address of the attendee on success;
            otherwise returns a null QString.
    \sa setAddress()
*/
QString XQCalendarAttendee::address() const
{
    return d ? d->m_address : QString();
}

/*!
    Sets the common name of the attendee.
    
    \param name Common name 
    \sa commonName()
*/
void XQCalendarAttendee::setCommonName(const QString& name)
{
    detach();
    d->m_commonName = name;
}

/*!
    Gets the common name of the attendee.
    
    \return The common name of the attendee on success;
            otherwise returns a null QString. 
    \sa setCommonName()
*/
QString XQCalendarAttendee::commonName() const
{
    return d ? d->m_commonName : QString();
}

/*!
    Sets the role of the attendee.
    
    \param role The role 
    \sa role()
*/
void XQCalendarAttendee::setRole(XQCalendarAttendee::ParticipantRole role)
{
    detach();
    d->m_role = role;
}

/*!
    Gets the role of the attendee.
    
    \return The role
    \sa setRole()
*/
XQCalendarAttendee::ParticipantRole XQCalendarAttendee::role() const
{
    return d ? d->m_role : ParticipantRoleUnknown;
}

/*!
    Sets the status of the attendee.
    
    \param status Attendees's status
    \sa status()
 */
void XQCalendarAttendee::setStatus(XQCalendarAttendee::StatusType status)
{
    detach();
    d->m_status = status;
}

/*!
    Gets the status of the attendee.
    
    \return Attendees's status
    \sa status()
 */
XQCalendarAttendee::StatusType XQCalendarAttendee::status() const
{
    return d ? d->m_status : StatusUnknown;
}

/*!
    Sets whether or not a response is/was requested for this attendee.
    
    \param responseRequested True if a response is/was requested, false if not.
    \sa responseRequested()
 */
void XQCalendarAttendee::setResponseRequested(bool responseRequested)
{
    detach();
    d->m_responseRequested = responseRequested;
}

/*!
    Sets whether or not a response is/was requested for this attendee.
    
    \return True if a response is/was requested, false if not.
    \sa setResponseRequested()
 */
bool XQCalendarAttendee::responseRequested() const
{
    return d ? d->m_responseRequested : false;
}

/*!
    Returns true if the attendee is empty; otherwise returns false.

    \return true if the attendee is empty; otherwise returns false.
*/
bool XQCalendarAttendee::isNull() const
{
    return !d;
}

void XQCalendarAttendee::detach()
{
    if (!d) {
        d = new XQCalendarAttendeePrivate;
    } else {
        qAtomicDetach(d);
    }
}

/*!
    Assigns \a other to this attendee and returns a reference
    to this attendee.

    \param other the other attendee
    \return a reference to this attendee
*/
XQCalendarAttendee& XQCalendarAttendee::operator=(const XQCalendarAttendee& other)
{
    if (d == other.d) 
    {
        return *this;
    }
    if (other.d) 
    {
        other.d->ref.ref();
    }
    if (d && !d->ref.deref()) 
    {
        delete d;
    }
    d = other.d;
    return *this;
}


/*!
    Returns true if this XQCalendarAttendee is equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarAttendee::operator==(const XQCalendarAttendee& other) const
{
    if (d == other.d)
        return true;
        
    return (d->m_address == other.d->m_address
            && d->m_commonName == other.d->m_commonName
            && d->m_responseRequested == other.d->m_responseRequested
            && d->m_role == other.d->m_role
            && d->m_status == other.d->m_status);
}

/*!
    Returns true if this XQCalendarAttendee is not equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarAttendee::operator!=(const XQCalendarAttendee& other) const
{
    return !(*this == other);
}

XQCalendarAttendeePrivate::XQCalendarAttendeePrivate() 
    : ref(1)
{ 
}

/****************************************************
 *
 * XQCalendarCategory
 *
 ****************************************************/

/*!
    \class XQCalendarCategory

    \brief Calendar categories can be associated with a calendar entry.
           There are 12 built in category types defined by CategoryType. 
           Additionally, it is possible to define extended category types which are held as a string.
           Any number of categories can be specified for an entry. 
           Calendar entry provides member functions for adding, deleting and fetching categories for an entry. 
*/

/*!
    \enum XQCalendarCategory::CategoryType

    This enum defines the possible category types for a XQCalendarCategory object.
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::AppointmentCategory
    Appointment
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::BusinessCategory
    Business
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::EducationCategory
    Education
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::HolidayCategory
    Holiday
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::MeetingCategory
    Meeting
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::MiscellaneousCategory
    All other types
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::PersonalCategory
    Personal
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::PhoneCallCategory
    Phone call
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::SickDayCategory
    Sick day
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::SpecialOccasionCategory
    Special occasion
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::TravelCategory
    Travel
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::VacationCategory
    Vacation
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::ExtendedCategory
     Extended 
*/
/*! \var XQCalendarCategory::CategoryType XQCalendarCategory::UnknownCategory
    Unknown
*/ 

/*!
    Creates a category.
*/
XQCalendarCategory::XQCalendarCategory()
    : d(NULL)
{
}

/*!
    Creates a copy of a given category.

   \param other catecory to be copied.
*/
XQCalendarCategory::XQCalendarCategory(const XQCalendarCategory& other) : d(other.d)
{
    if (d) {
        d->ref.ref();
    }
}

/*!
    Constructs a new category using given \a category.

    \param category The type of the category
*/
XQCalendarCategory::XQCalendarCategory(XQCalendarCategory::CategoryType category) 
    : d(new XQCalendarCategoryPrivate)
{
    d->m_categoryType = category;
}

/*!
    Destroys the category.
*/
XQCalendarCategory::~XQCalendarCategory()
{
    if (d && !d->ref.deref()) 
    {
        delete d;
    }
}

/*!
    Sets the category type.
    
    \param categoryType The category type 
    \sa category()
*/
void XQCalendarCategory::setCategory(XQCalendarCategory::CategoryType categoryType)
{
    detach();
    d->m_categoryType = categoryType;
}

/*!
    Sets the extended category name. 
    
    \param name The entended category name 
    \sa extendedCategoryName()
*/
void XQCalendarCategory::setExtendedCategoryName(const QString& name)
{
    detach();
    d->m_categoryType = XQCalendarCategory::ExtendedCategory;
    d->m_extendedCategory = name;
}

/*!
    Gets the extended category name. 
    
    \return The entended category name 
    \sa setExtendedCategoryName()
*/
QString XQCalendarCategory::extendedCategoryName() const
{
    return d ? d->m_extendedCategory : QString();
}

/*!
    Gets the category type.
    
    \return The category type
    \sa setCategory()
*/
XQCalendarCategory::CategoryType XQCalendarCategory::category() const
{
    return d ? d->m_categoryType : UnknownCategory;
}

void XQCalendarCategory::detach()
{
    if (!d) {
        d = new XQCalendarCategoryPrivate();
    } else {
        qAtomicDetach(d);
    }
}

/*!
    Assigns \a other to this category and returns a reference
    to this category.

    \param other the other category
    \return a reference to this category
*/
XQCalendarCategory& XQCalendarCategory::operator=(const XQCalendarCategory& other)
{
    if (d == other.d) 
    {
        return *this;
    }
    if (other.d) 
    {
        other.d->ref.ref();
    }
    if (d && !d->ref.deref()) 
    {
        delete d;
    }
    d = other.d;
    return *this;
}

/*!
    Returns true if this XQCalendarCategory is equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarCategory::operator==(const XQCalendarCategory& other) const
{
    if (d == other.d)
        return true;
        
    return (d->m_categoryType == other.d->m_categoryType
            && d->m_extendedCategory == other.d->m_extendedCategory);
}

/*!
    Returns true if this XQCalendarAttendee is not equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarCategory::operator!=(const XQCalendarCategory& other) const
{
    return !(*this == other);
}

/*!
    Returns true if the category is empty; otherwise returns false.

    \return true if the category is empty; otherwise returns false.
*/
bool XQCalendarCategory::isNull() const
{
    return !d;
}

XQCalendarCategoryPrivate::XQCalendarCategoryPrivate() 
    : m_categoryType(XQCalendarCategory::UnknownCategory)
{  
}

/****************************************************
 *
 * XQCalendarAlarm
 *
 ****************************************************/

/*!
    \class XQCalendarAlarm

    \brief Class representing an alarm.
           This can be assigned to a calendar entry.
*/

/*!
    Creates an alarm.
*/
XQCalendarAlarm::XQCalendarAlarm() : d(NULL)
{
}

/*!
    Creates a copy of a given alarm.

   \param other alarm to be copied.
*/
XQCalendarAlarm::XQCalendarAlarm(const XQCalendarAlarm& other) : d(other.d)
{
    if (d) {
        d->ref.ref();
    }
}

/*!
    Destroys the alarm.
*/
XQCalendarAlarm::~XQCalendarAlarm()
{
    if (d && !d->ref.deref()) 
    {
        delete d;
    }
}

/*! \var XQCalendarAlarm::MaxFileNameLength
    Maximum file lenght for the alarm
*/

/*!
    Sets a time offset for an alarm to occur prior to a scheduled event.
    The time offset is calculated as the number of minutes before the instance time of the event.
    It is possible to have a negative offset provided that the alarm is 
    on the same day (in local time) as the instance time; this means the alarm occurs 
    after the event.
    
    \param minutes The time offset in minutes for an alarm prior to an event. 
    \sa timeOffset()
*/
void XQCalendarAlarm::setTimeOffset(int minutes)
{
    detach();
    d->m_timeOffset = minutes;
}

/*!
    Gets the time offset for the alarm to occur prior to an event. 
    
    \return The alarm offset (in minutes) prior to an event on success;
            otherwise return -1.
    \sa setTimeOffset()
*/
int XQCalendarAlarm::timeOffset() const
{
    return d ? d->m_timeOffset : -1;
}
 
/*!
    Sets the name of the alarm sound.
    If this isn't set then the default alarm sound will be used.
    Note: if the length of the new alarm sound name is greater than MaxFileNameLength characters, 
    it will be ignored.
    
    \param alarmSoundName Sound name
    \sa alarmSoundName()
*/
void XQCalendarAlarm::setAlarmSoundName(const QString& alarmSoundName)
{
    detach();
    d->m_soundName = alarmSoundName;
}

/*!
    Gets the name of the alarm sound.
    
    \return Sound name on success;
            otherwise returns a null QString.
    
    \sa setAlarmSoundName()
*/
QString XQCalendarAlarm::alarmSoundName() const
{
    return d ? d->m_soundName : QString();
}

/*!
    Returns true if the alarlm is empty; otherwise returns false.

    \return true if the alarm is empty; otherwise returns false.
*/
bool XQCalendarAlarm::isNull() const
{
    return !d;
}

/*!
    Assigns \a other to this alarm and returns a reference
    to this alarm.

    \param other the other alarm
    \return a reference to this alarm
*/
XQCalendarAlarm& XQCalendarAlarm::operator=(const XQCalendarAlarm& other)
{
    if (d == other.d) 
    {
        return *this;
    }
    if (other.d) 
    {
        other.d->ref.ref();
    }
    if (d && !d->ref.deref()) 
    {
        delete d;
    }
    d = other.d;
    return *this;
}

/*!
    Returns true if this XQCalendarAlarm is equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarAlarm::operator==(const XQCalendarAlarm& other) const
{
    if (d == other.d)
        return true;
        
    return (d->m_soundName == other.d->m_soundName
            && d->m_timeOffset == other.d->m_timeOffset);
}

/*!
    Returns true if this XQCalendarAlarm is not equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarAlarm::operator!=(const XQCalendarAlarm& other) const
{
    return !(*this == other);
}

void XQCalendarAlarm::detach()
{
    if (!d) {
        d = new XQCalendarAlarmPrivate;
    } else {
        qAtomicDetach(d);
    }
}

XQCalendarAlarmPrivate::XQCalendarAlarmPrivate() : ref(1)
{
    
}

/****************************************************
 *
 * XQCalendarRepeatRule
 *
 ****************************************************/

/*!
    \class XQCalendarRepeatRule

    \brief Class representing a repeat rule types.
           
           This supports the following standard iCal properties:
        
           FREQ (rule type),
           DTSTART (start date),
           UNTIL (end date),
           COUNT (number of instances),
           INTERVAL (interval between instances),
           BYDAY,
           BYMONTHDAY,
           BYYEARDAY,
           WKST (start day of week).
           
           Note that the repeat rule type (FREQ) must be set before any of the following properties
           can be set, since their behaviour is dependent on the rule type: 
           BYDAY, BYMONTHDAY, BYYEARDAY
           The WKST parameter is only significant in weekly repeat rules with an interval of 
           greater than 1.

           The repeat rule type may not be changed once it has been set.
*/

/*!
    \enum XQCalendarRepeatRule::RuleType

    This enum defines the possible rule types for a XQCalendarRepeatRule object.
*/
/*! \var XQCalendarRepeatRule::RuleType XQCalendarRepeatRule::DailyRule
    Rule which repeats based on a number of days.
*/
/*! \var XQCalendarRepeatRule::RuleType XQCalendarRepeatRule::WeeklyRule
    Rule which repeats based on a number of weeks.
*/
/*! \var XQCalendarRepeatRule::RuleType XQCalendarRepeatRule::MonthlyRule
    Rule which repeats based on a number of months.
*/
/*! \var XQCalendarRepeatRule::RuleType XQCalendarRepeatRule::YearlyRule
    Rule which repeats based on a number of years.
*/
/*! \var XQCalendarRepeatRule::RuleType XQCalendarRepeatRule::InvalidRule
     The type has not yet been defined.
*/

/*!
    \enum XQCalendarRepeatRule::Day

    The days are presented as enums
*/
/*! \var XQCalendarRepeatRule::Day XQCalendarRepeatRule::Monday */
/*! \var XQCalendarRepeatRule::Day XQCalendarRepeatRule::Tuesday */
/*! \var XQCalendarRepeatRule::Day XQCalendarRepeatRule::Wednesday */
/*! \var XQCalendarRepeatRule::Day XQCalendarRepeatRule::Thursday */
/*! \var XQCalendarRepeatRule::Day XQCalendarRepeatRule::Friday */
/*! \var XQCalendarRepeatRule::Day XQCalendarRepeatRule::Saturday */
/*! \var XQCalendarRepeatRule::Day XQCalendarRepeatRule::Sunday */
/*! \var XQCalendarRepeatRule::Day XQCalendarRepeatRule::InvalidDay */

/*!
    \enum XQCalendarRepeatRule::Day

    The months are presented as enums
*/
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::January */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::February */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::March */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::April */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::May */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::June */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::July */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::August */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::September */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::October */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::November */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::December */
/*! \var XQCalendarRepeatRule::Month XQCalendarRepeatRule::InvalidMonth */

/*!
    Creates a repeat rule.
*/
XQCalendarRepeatRule::XQCalendarRepeatRule() : d(NULL)
{
    
}

/*!
    Constructs a new repeat rule using given \a type.

    \param type The type of the rule
*/
XQCalendarRepeatRule::XQCalendarRepeatRule(XQCalendarRepeatRule::RuleType type) 
    : d(new XQCalendarRepeatRulePrivate)
{  
    d->m_repeatRuleType = type;
    d->ref.ref();
}

/*!
    Creates a copy of a given repeat rule.

   \param other repeat rule to be copied.
*/
XQCalendarRepeatRule::XQCalendarRepeatRule(const XQCalendarRepeatRule& other)
    : d(other.d)
{
    if (d) {
        d->ref.ref();
    }    
}

/*!
    Destroys the repeat rule.
*/
XQCalendarRepeatRule::~XQCalendarRepeatRule()
{
    if (d && !d->ref.deref()) 
    {
        delete d;
    }
}

/*!
    Sets the repeat definition's type.
    This will be one of: daily, weekly, monthly or yearly. 
    If the type is weekly, it must have at least one weekday set by calling setByDay().
    The type may only be set once, from either the constructor or from the setType() function. 

    \param type The repeat definition's type. 
    \sa type()
*/
void XQCalendarRepeatRule::setType(XQCalendarRepeatRule::RuleType type)
{
    detach();
    d->m_repeatRuleType = type;   
}

/*!
    Gets the repeat definition's type.
    This will be one of: daily, weekly, monthly or yearly.

    \return The repeat definition's type. 
    \sa setType()
*/
XQCalendarRepeatRule::RuleType XQCalendarRepeatRule::type() const
{
    return d ? d->m_repeatRuleType : InvalidRule;
}

/*!
    Sets the repeat interval.
    This is a number of days for a daily repeat, a number of weeks for a weekly repeat, etc.
    
    \param interval Any parameter that is greater than 255 or less than 1 will be ignored. 
    \sa interval() 
*/
void XQCalendarRepeatRule::setInterval(int interval)
{
    detach();
    if (interval <= 255 && interval >= 1)
    {
        d->m_interval = interval;    
    }
}

/*!
    Gets the repeat interval.
    This is a number of days for a daily repeat, a number of weeks for a weekly repeat, etc.
    
    \return The interval in minutes on success;
            otherwise returns -1.
    
    \sa interval() 
*/
int XQCalendarRepeatRule::interval() const
{
    return d ? d->m_interval : -1;
}

/*!
    Sets the repeat's start date.
    
    \param date The start date
    \sa repeatRuleStart()
*/
void XQCalendarRepeatRule::setRepeatRuleStart(const QDate& date)
{
    detach();
    d->m_startDate = date;
}

/*!
    Gets the repeat's start date.
    
    \return The start date on success;
            otherwise returns a null QDate.
    
    \sa setRepeatRuleStart()
*/
QDate XQCalendarRepeatRule::repeatRuleStart() const
{
    return d ? d->m_startDate : QDate();
}

/*!
    Sets the repeat's end date.
    
    \parm date The end date
    \sa setUntil()
*/
void XQCalendarRepeatRule::setUntil(const QDate& date)
{
    detach();
    d->m_untilDate = date;
}

/*!
    Gets the repeat's end date.
    
    \return The end date on success;
            otherwise returns a null QDate. 
    \sa setUntil()
*/
QDate XQCalendarRepeatRule::until() const
{
    return d ? d->m_untilDate : QDate();
}

/*!
    Sets the first day of the week for this repeat rule.
    
    \param day The weekday to be the first
    \sa weekStart()
*/
void XQCalendarRepeatRule::setWeekStart(Day day)
{
    detach();
    d->m_weekStartDay = day;
}

/*!
    Gets the first day of the week for this repeat rule.
    
    \return The first weekday 
    \sa setWeekStart()
*/
XQCalendarRepeatRule::Day XQCalendarRepeatRule::weekStart() const
{
    return d ? d->m_weekStartDay : InvalidDay;
}

/*!
    Set all weekdays on which this rule is repeated.
    
    \param days List containing all weekdays that are to be set. 
           Any weekdays not included in this array will not be set. 
    \sa getByDay()
*/
void XQCalendarRepeatRule::setByDay(const QList<Day>& days)
{
    detach();
    d->m_days = days;   
}

/*!
    Gets all weekdays on which this rule is repeated.
    
    \return List contains all weekdays that are to be set on success;
            otherwise returns a null list.  
    \sa setByDay()
*/
QList<XQCalendarRepeatRule::Day> XQCalendarRepeatRule::byDay() const
{
    return d ? d->m_days : QList<XQCalendarRepeatRule::Day>();
}

/*!
    Sets all dates of the month on which this rule is repeated.
    
    \param monthDays List containing all month dates that are to be set.   
    \sa byMonthDay()
*/
void XQCalendarRepeatRule::setByMonthDay(const QList<int>& monthDays)
{
    detach();
    d->m_monthDays = monthDays;
}

/*!
    Gets all dates of the month on which this rule is repeated.
    
    \return List contains all month dates that are to be set on success;
            otherwise returns a null list.
    
    \sa setByMonthDay()
*/
QList<int> XQCalendarRepeatRule::byMonthDay() const
{
    return d ? d->m_monthDays : QList<int>();
}

/*!
    Sets the month of the year for this repeat rule.
    
    \param months List of months on which to repeat. 
    Only the first month in the array is used. 
    \sa byMonth()
*/
void XQCalendarRepeatRule::setByMonth(const QList<Month>& months)
{
    detach();
    d->m_months = months;
}

/*!
    Gets the month of the year for this repeat rule.
    
    \return List of months on which to repeat on success;
            otherwise returns a null list.
    . 
    \sa setByMonth()
*/
QList<XQCalendarRepeatRule::Month> XQCalendarRepeatRule::byMonth() const
{
    return d ? d->m_months : QList<XQCalendarRepeatRule::Month>();
}

void XQCalendarRepeatRule::detach()
{
    if (!d) {
        d = new XQCalendarRepeatRulePrivate();
    } else {
        qAtomicDetach(d);
    }
}

/*!
    Assigns \a other to this repeat rule and returns a reference
    to this repeat rule.

    \param other the other repeat rule
    \return a reference to this repeat rule
*/
XQCalendarRepeatRule& XQCalendarRepeatRule::operator=(const XQCalendarRepeatRule& other)
{
    if (d == other.d) 
    {
        return *this;
    }
    if (other.d) 
    {
        other.d->ref.ref();
    }
    if (d && !d->ref.deref()) 
    {
        delete d;
    }
    d = other.d;
    return *this;
}


/*!
    Returns true if this XQCalendarRepeatRule is equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarRepeatRule::operator==(const XQCalendarRepeatRule& other) const
{
    if (d == other.d)
        return true;
    
    return (d->m_days == other.d->m_days
            && d->m_interval == other.d->m_interval
            && d->m_monthDays == other.d->m_monthDays
            && d->m_months == other.d->m_months
            && d->m_repeatRuleType == other.d->m_repeatRuleType
            && d->m_startDate == other.d->m_startDate
            && d->m_untilDate == other.d->m_untilDate
            && d->m_weekStartDay == other.d->m_weekStartDay);
}

/*!
    Returns true if this XQCalendarRepeatRule is not equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarRepeatRule::operator!=(const XQCalendarRepeatRule& other) const
{
    return !(*this == other);
}

XQCalendarRepeatRulePrivate::XQCalendarRepeatRulePrivate() : ref(1)
{
    
}

/****************************************************
 *
 * XQCalendarEntry
 *
 ****************************************************/

/*!
    \class XQCalendarEntry

    \brief Class representing a calendar entry. 
    This can be an appointment, to-do item, reminder, event or anniversary.
    XQCalendarEntry contains information about a calendar entry. 
*/

/*!
    \enum XQCalendarEntry::Type

    This enum defines the possible entry types for a XQCalendarEntry object.
*/
/*! \var XQCalendarEntry::Type XQCalendarEntry::TypeAppoinment
    An appointment, which has a start time and end time.
*/
/*! \var XQCalendarEntry::Type XQCalendarEntry::TypeTodo
    A to-do, which can have a start time and end time (the end time is the due date), or can be undated.
*/
/*! \var XQCalendarEntry::Type XQCalendarEntry::TypeEvent
    An event, which has a start time and end time.
*/
/*! \var XQCalendarEntry::Type XQCalendarEntry::TypeReminder
    A reminder, which has a start time only.
*/
/*! \var XQCalendarEntry::Type XQCalendarEntry::TypeAnniversary
    An anniversary, which has a start time and end time.
*/
/*! \var XQCalendarEntry::Type XQCalendarEntry::TypeUnknown
    The type is unknown.
*/

/*!
    \enum XQCalendarEntry::Method

    This enum defines the possible methods for a XQCalendarEntry object.
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodNone
    The RFC2445-defined method value 'None'. 
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodPublish
    The RFC2445-defined method value 'Publish'.
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodRequest
    The RFC2445-defined method value 'Request'.
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodReply
    The RFC2445-defined method value 'Reply'.
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodAdd
    The RFC2445-defined method value 'Add'.
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodCancel
    The RFC2445-defined method value 'Cancel'.
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodRefresh
    The RFC2445-defined method value 'Refresh'.
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodCounter
    The RFC2445-defined method value 'Counter'.
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodDeclineCounter
    The RFC2445-defined method value 'DeclineCounter'.
*/
/*! \var XQCalendarEntry::Method XQCalendarEntry::MethodUnknown
    The method is unknown
*/

/*!
    Creates a calendar entry.
*/
XQCalendarEntry::XQCalendarEntry() : d(NULL)
{
}

/*!
    Constructs a new entry rule using given \a type.

    \param type The type of the entry
*/
XQCalendarEntry::XQCalendarEntry(Type type) : d(new XQCalendarEntryPrivate)
{ 
    d->m_entryType = type;
    d->ref.ref();
}

/*!
    Creates a copy of a given entry.

   \param other entry to be copied.
*/
XQCalendarEntry::XQCalendarEntry(const XQCalendarEntry& other) : d(other.d)
{
    if (d) {
        d->ref.ref();
    }
}

/*!
    Destroys the entry.
*/
XQCalendarEntry::~XQCalendarEntry()
{
    if (d && !d->ref.deref()) 
    {
        delete d;
    }
}

/*!
   Adds an attendee for this entry.

   \param The attendee to be added.
   \sa attendies(), deleteAttendee()
*/
void XQCalendarEntry::addAttendee(const XQCalendarAttendee& attendee)
{
    detach();
    d->addAttendee(attendee);
}

/*!
    Returns true if the calendar entry is empty; otherwise returns false.

    \return true if the Calendar entry is empty; otherwise returns false.
*/
bool XQCalendarEntry::isNull() const
{
    return !d;
}

/*!
    Sets the alarm for the entry. Alarm can be removed by setting null XQCalendarAlarm
    with this function.

   \param alarm Alarm object to be set
   \sa alarm()
*/
void XQCalendarEntry::setAlarm(const XQCalendarAlarm& alarm)
{
    detach();
    d->m_alarm = alarm;
}

/*!
    Gets the alarm for the entry

   \return Alarm object on success;
           otherwise returns a null XQCalendarAlarm.
   
   \sa setAlarm()
*/
XQCalendarAlarm XQCalendarEntry::alarm() const
{
    return d ? d->m_alarm : XQCalendarAlarm();
}

/*!
    Sets the start and end date/times for an entry.

    For an appointment, event or anniversary, the start time must be earlier 
    than or equal to the end time. For a reminder, the end time will be ignored. 
    For a to-do entry, the end time is the 'due date'. The time portion of the start date 
    will not be stored for todos, only the number of days until the due date. 
    Only Undated Todo's can have both start and end date as NullTime.

    \param startTime The entry's new start date/time.
    \param endTime The entry's new end date/time.
    \return true if the start and end times are valid; otherwise returns false.
    \sa startTime(), endTime()
*/
bool XQCalendarEntry::setStartAndEndTime(const QDateTime& startTime, const QDateTime& endTime)
{
    detach();
    d->m_startTime = startTime;
    d->m_endTime = endTime;

    return true;
}

/*!
    Gets the start date/time for an entry.

   \return The entry's start date/time on success;
           otherwise returns a null QDateTime.
   
   \sa endTime(), setStartAndEndTime()
*/
QDateTime XQCalendarEntry::startTime() const
{
    return d ? d->m_startTime : QDateTime();
}

/*!
    Gets the entry's end date/time.

   \return The entry's end date/time on success;
           otherwise returns a null QDateTime.
   \sa startTime(), setStartAndEndTime()
*/
QDateTime XQCalendarEntry::endTime() const
{
    return d ? d->m_endTime : QDateTime();
}

/*!
    Returns a reference to the attendees list.
    Using a reference makes it possible to manipulate the list directly.

    \return A reference to the attendees list
    \sa startTime(), setStartAndEndTime()
*/
QList<XQCalendarAttendee>& XQCalendarEntry::attendees()
{
    return d->m_attendees;
}

/*!
    Returns a const reference to the attendees list.

    \return A const reference to the attendees list
    \sa startTime(), setStartAndEndTime()
*/
const QList<XQCalendarAttendee>& XQCalendarEntry::attendees() const
{
    return d->m_attendees;
}

/*!
    Returns a const reference to the attendees list.

    \return A const reference to the attendees list
    \sa addCategory(), deleteCategory()
*/
const QList<XQCalendarCategory>& XQCalendarEntry::categories() const
{
    return d->m_categories;
}

/*!
    Sets the description text for this entry.

    \param description The description text
    \sa description()
*/
void XQCalendarEntry::setDescription(const QString& description)
{
    detach();
    d->m_description = description;
}

/*!
    Gets the description text for the entry.

    \return The description text on success;
            otherwise returns a null QString.
    \sa setDescription()
*/
QString XQCalendarEntry::description() const
{
    return d ? d->m_description : QString();
}

/*!
    Gets a list of the entry's categories.

    \return A const reference to the attendees list
    \sa addCategory(), deleteCategory()
*/
QList<XQCalendarCategory>& XQCalendarEntry::categories()
{
    return d->m_categories;
}

/*!
    Gets an id of the entry.

    \return Entry id on success;
           otherwise returns -1.
*/
ulong XQCalendarEntry::id() const
{
    return d ? d->m_id : -1;
}

/*!
    Gets the type of entry.

   \return The type of entry.
*/
XQCalendarEntry::Type XQCalendarEntry::type() const
{
    return d ? d->m_entryType : TypeUnknown;
}

/*!
    Sets the type of entry.

   \param type The type of entry.
   \sa type()
*/
void XQCalendarEntry::setType(Type type)
{
    detach();
    d->m_entryType = type;
}

/*!
    Appends a category to the entry's list of categories.

    \param category The category to be added
    \sa deleteCategory(), categories()
*/
void XQCalendarEntry::addCategory(const XQCalendarCategory& category)
{
    detach();
    d->addCategory(category);
}

/*!
    Sets the contents of the entry's location field.

    \return Descriptor containing a location, e.g. for a meeting.
    \sa location()
*/
void XQCalendarEntry::setLocation(const QString& location)
{
    detach();
    d->m_location = location;
}

/*!
    Gets the contents of the entry's location field.

    \return The location field on success;
           otherwise returns a null QString.
    \sa setLocation()
*/
QString XQCalendarEntry::location() const
{
    return d ? d->m_location : QString();
}

/*!
    Sets the summary text for this entry.

    \param summary The summary text.
    \sa summary()
*/
void XQCalendarEntry::setSummary(const QString& summary)
{
    detach();
    d->m_summaryText = summary;
}

/*!
    Gets the summary for the entry.

    \return The summary text on success;
            otherwise returns a null QString.
    \sa setSummary()
*/
QString XQCalendarEntry::summary() const
{
    return d ? d->m_summaryText : QString();
}

/*!
    Sets the entry's method property for group scheduling.

    \param method The method property of a Group Scheduling entry
    \sa method()
*/
void XQCalendarEntry::setMethod(Method method)
{
    detach();
    d->m_method = method;
}


/*!
    Returns the entry's method property for group scheduling.

    \return The method property of a Group Scheduling entry
    \sa setMethod()
*/
XQCalendarEntry::Method XQCalendarEntry::method() const
{
    return d ? d->m_method : MethodUnknown;
}

/*!
    Sets the entry's repeat definition.
    
    \param repetRule Repeat rule object
    \sa repeatRule()
*/
void XQCalendarEntry::setRepeatRule(const XQCalendarRepeatRule& repeatRule)
{
    detach();
    d->m_repeatRule = repeatRule;
}

/*!
    Gets the entry's repeat rule. Count and the Until values can be accessed.
    Note! In the case of a repeat rule which repeats forever, the Count will always be returned as 0.
    
    return Repeat rule object on success;
           otherwise returns a null XQCalendarRepeatRule.
    \sa setRepeatRule()
*/
XQCalendarRepeatRule XQCalendarEntry::repeatRule() const
{
   return d ? d->m_repeatRule : XQCalendarRepeatRule();
}

/*!
    Sets the priority for the entry. The default value is zero.
    
    \param priority Priority value between 0 and 255. The behaviour is undefined if the priority is greater than 255.
    \sa priority() 
*/
void XQCalendarEntry::setPriority(int priority)
{
    detach();
    d->m_priority = priority;
}

/*!
    Gets the priority of the entry.
    
    return Priority value between 0 and 255 on success;
           otherwise returns -1.
    \sa setPriority()
*/
int XQCalendarEntry::priority() const
{
    return d ? d->m_priority : -1;
}

void XQCalendarEntry::detach()
{
    if (!d) {
        d = new XQCalendarEntryPrivate;
    } else {
        qAtomicDetach(d);
    }
}

/*!
    Assigns \a other to this entry and returns a reference
    to this entry.

    \param other the other entry
    \return a reference to this entry
*/
XQCalendarEntry& XQCalendarEntry::operator=(const XQCalendarEntry& other)
{
    if (d == other.d) 
    {
        return *this;
    }
    if (other.d) 
    {
        other.d->ref.ref();
    }
    if (d && !d->ref.deref()) 
    {
        delete d;
    }
    d = other.d;
    return *this;
}

/*!
    Returns true if this XQCalendarEntry is equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarEntry::operator==(const XQCalendarEntry& other) const
{
    if (d == other.d)
        return true;
    
    return (d->m_alarm == other.d->m_alarm
            && d->m_attendees == other.d->m_attendees
            && d->m_categories == other.d->m_categories
            && d->m_description == other.d->m_description
            && d->m_endTime == other.d->m_endTime
            && d->m_entryType == other.d->m_entryType
            && d->m_id == other.d->m_id
            && d->m_location == other.d->m_location
            && d->m_method == other.d->m_method
            && d->m_priority == other.d->m_priority
            && d->m_repeatRule == other.d->m_repeatRule
            && d->m_startTime == other.d->m_startTime
            && d->m_summaryText == other.d->m_summaryText);
}

/*!
    Returns true if this XQCalendarEntry is not equal to the \a other
    info, otherwise returns false.
*/
bool XQCalendarEntry::operator!=(const XQCalendarEntry& other) const
{
    return !(*this == other);
}

XQCalendarEntryPrivate::XQCalendarEntryPrivate() : ref(1), m_method(XQCalendarEntry::MethodNone)
{

}

bool XQCalendarEntryPrivate::deleteCategory(const XQCalendarCategory& category)
{
    for (int i = 0; i < m_categories.count(); i++)
    {
        if (m_categories.at(i) == category)
        {
            m_categories.removeAt(i);
            return true;
        }
    }
    return false;    
}

void XQCalendarEntryPrivate::addCategory(const XQCalendarCategory& category)
{
    m_categories.append(category);
}

bool XQCalendarEntryPrivate::deleteAttendee(const XQCalendarAttendee& attendee)
{
    for (int i = 0; i < m_attendees.count(); i++)
    {
        if (m_attendees.at(i).address() == attendee.address())
        {
            m_attendees.removeAt(i);
            return true;
        }
    }
    return false;
}

void XQCalendarEntryPrivate::addAttendee(const XQCalendarAttendee& attendee)
{
    m_attendees.append(attendee);    
}


// End of file
