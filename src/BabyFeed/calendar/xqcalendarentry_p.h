#ifndef XQCALENDARENTRY_P_H
#define XQCALENDARENTRY_P_H

// INCLUDES
#include "xqcalendarentry.h"
#include <QTime>

// CLASS DECLARATION
class XQCalendarAttendeePrivate
{
public:
    XQCalendarAttendeePrivate();

public:
    QAtomicInt ref;
    
private:
    friend class XQCalendarAttendee;
    QString m_address;
    XQCalendarAttendee::ParticipantRole m_role;
    XQCalendarAttendee::StatusType m_status;
    QString m_commonName;

    bool m_responseRequested;
};

class XQCalendarCategoryPrivate
{
public:
    XQCalendarCategoryPrivate();

public:
    QAtomicInt ref;
 
private:
    friend class XQCalendarCategory;
    XQCalendarCategory::CategoryType m_categoryType;
    QString m_extendedCategory;
};

class XQCalendarAlarmPrivate
{
public:
    XQCalendarAlarmPrivate();

public:
    QAtomicInt ref;

private:
    friend class XQCalendarAlarm;
    QString m_soundName;
    int m_timeOffset;
};

class XQCalendarRepeatRulePrivate
{
public:
    XQCalendarRepeatRulePrivate();

public:
    QAtomicInt ref;

private:
    friend class XQCalendarRepeatRule;
    XQCalendarRepeatRule::RuleType m_repeatRuleType;
    QList<XQCalendarRepeatRule::Day> m_days;
    QList<XQCalendarRepeatRule::Month> m_months;
    QList<int> m_monthDays;
    XQCalendarRepeatRule::Day m_weekStartDay;
    QDate m_startDate;
    QDate m_untilDate;
    int m_interval;
};

class XQCalendarEntryPrivate
{
public:
    XQCalendarEntryPrivate();
    void addCategory(const XQCalendarCategory& category);
    bool deleteCategory(const XQCalendarCategory& category);
    void addAttendee(const XQCalendarAttendee& attendee);
    bool deleteAttendee(const XQCalendarAttendee& attendee);

public:
    QAtomicInt ref;
    
private:
    friend class XQCalendarEntry;
    friend class XQCalendarPrivate;
    QList<XQCalendarAttendee> m_attendees;
    QList<XQCalendarCategory> m_categories;
    QDateTime m_startTime;
    QDateTime m_endTime;
    QString m_summaryText;
    QString m_location;
    ulong m_id;
    QString m_description;
    XQCalendarEntry::Type m_entryType;
    XQCalendarEntry::Method m_method;
    XQCalendarAlarm m_alarm;
    XQCalendarRepeatRule m_repeatRule;
    int m_priority;
};

#endif // XQCALENDARENTRY_P_H

// End of file
