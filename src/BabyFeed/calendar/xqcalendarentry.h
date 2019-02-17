#ifndef XQCALENDARENTRY_H
#define XQCALENDARENTRY_H

// INCLUDES
#include <QObject>
#include "calendar_global.h"

// FORWARD DECLARATIONS
class QDate;
class QDateTime;
class XQCalendarAlarmPrivate;
class XQCalendarAttendeePrivate;
class XQCalendarCategoryPrivate;
class XQCalendarEntryPrivate;
class XQCalendarRepeatRulePrivate;

// CLASS DECLARATION
class XQCALENDAR_EXPORT XQCalendarAttendee
{
public:
    enum ParticipantRole
    {
        RequiredParticipant = 0,
        OptionalParticipant,
        NonParticipant,
        ChairParticipant,
        ParticipantRoleUnknown = -1
    };

    enum StatusType
    {
        StatusNeedsAction = 0,
        StatusAccepted,
        StatusTentative,
        StatusConfirmed,
        StatusDeclined,
        StatusCompleted,
        StatusDelegated,
        StatusInProcess,
        StatusUnknown = -1
    };
    
    XQCalendarAttendee();
    ~XQCalendarAttendee();
    XQCalendarAttendee(const QString& address);
    XQCalendarAttendee(const XQCalendarAttendee& other);
    
    void setAddress(const QString& address);
    void setCommonName(const QString& name);
    void setResponseRequested(bool responseRequested);
    void setRole(ParticipantRole role);
    void setStatus(StatusType status);

    QString address() const;
    QString commonName() const;
    bool responseRequested() const; 
    ParticipantRole role() const;
    StatusType status() const;

    bool isNull() const;
    
    XQCalendarAttendee& operator=(const XQCalendarAttendee& other);
    bool operator==(const XQCalendarAttendee& other) const;
    bool operator!=(const XQCalendarAttendee& other) const;
    
private:
    void detach();

private:
    XQCalendarAttendeePrivate* d;
    
};


class XQCALENDAR_EXPORT XQCalendarCategory
{
public:
    enum CategoryType 
    {
        AppointmentCategory,
        BusinessCategory,
        EducationCategory,  
        HolidayCategory,
        MeetingCategory,
        MiscellaneousCategory, 
        PersonalCategory,
        PhoneCallCategory,
        SickDayCategory,
        SpecialOccasionCategory,
        TravelCategory,
        VacationCategory,
        ExtendedCategory,
        UnknownCategory = -1
    };
    
    XQCalendarCategory();
    XQCalendarCategory(CategoryType category);
    XQCalendarCategory(const XQCalendarCategory& other);
    ~XQCalendarCategory();
    
    void setCategory(CategoryType categoryType);
    CategoryType category() const;
    
    void setExtendedCategoryName(const QString& name);
    QString extendedCategoryName() const;
    
    bool isNull() const;
    
    XQCalendarCategory& operator=(const XQCalendarCategory& other);
    bool operator==(const XQCalendarCategory& other) const;
    bool operator!=(const XQCalendarCategory& other) const;
    
private:
    void detach();

private:
    XQCalendarCategoryPrivate* d;
    
};


class XQCALENDAR_EXPORT XQCalendarAlarm
{
public:
    static const int MaxFileNameLength = 256;
    
    XQCalendarAlarm();
    XQCalendarAlarm(const XQCalendarAlarm& other);
    ~XQCalendarAlarm();
    
    void setTimeOffset(int minutes);
    void setAlarmSoundName(const QString& alarmSoundName);
    QString alarmSoundName() const;
    int timeOffset() const;
    
    bool isNull() const;
    
    XQCalendarAlarm& operator=(const XQCalendarAlarm& other);
    bool operator==(const XQCalendarAlarm& other) const;
    bool operator!=(const XQCalendarAlarm& other) const;
    
private:
    void detach();
    
private:
    XQCalendarAlarmPrivate* d;

};

class XQCALENDAR_EXPORT XQCalendarRepeatRule
{
public:
    
    enum RuleType
    {
        DailyRule,
        WeeklyRule,
        MonthlyRule,
        YearlyRule,
        InvalidRule = -1
    };
    
    enum Day
    {
        Monday,
        Tuesday, 
        Wednesday, 
        Thursday, 
        Friday, 
        Saturday, 
        Sunday,
        InvalidDay = -1
    };
    
    enum Month
    {
        January, 
        February, 
        March, 
        April, 
        May, 
        June, 
        July,
        August, 
        September, 
        October, 
        November, 
        December,
        InvalidMonth = -1 
    };
     
    XQCalendarRepeatRule();
    XQCalendarRepeatRule(RuleType type);
    XQCalendarRepeatRule(const XQCalendarRepeatRule& other);
    ~XQCalendarRepeatRule();
    
    void setType(RuleType type);
    RuleType type() const;
    
    int count() const;
    
    void setInterval(int interval);
    int interval() const;
    
    void setUntil(const QDate& date);
    QDate until() const;
    
    void setRepeatRuleStart(const QDate& date);
    QDate repeatRuleStart() const;
    
    void setWeekStart(Day day);
    Day weekStart() const;

    void setByDay(const QList<Day>& days);
    QList<Day> byDay() const;

    void setByMonthDay(const QList<int>& monthDays);
    QList<int> byMonthDay() const;
    
    void setByMonth(const QList<Month>& months); 
    QList<Month> byMonth() const;
    
    XQCalendarRepeatRule& operator=(const XQCalendarRepeatRule& other);
    bool operator==(const XQCalendarRepeatRule& other) const;
    bool operator!=(const XQCalendarRepeatRule& other) const;

private:
    void detach();
    
private:
    XQCalendarRepeatRulePrivate* d;
    
};


class XQCALENDAR_EXPORT XQCalendarEntry
{
public:

    enum Type
    {
        TypeAppoinment,
        TypeTodo,
        TypeEvent,
        TypeReminder,
        TypeAnniversary,
        TypeUnknown = -1
    };
    
    enum Method
    {
        MethodNone,
        MethodPublish, 
        MethodRequest, 
        MethodReply, 
        MethodAdd, 
        MethodCancel, 
        MethodRefresh,          
        MethodCounter,          
        MethodDeclineCounter,
        MethodUnknown = -1
    };
 
    XQCalendarEntry();
    XQCalendarEntry(Type type);
    XQCalendarEntry(const XQCalendarEntry& other);
    ~XQCalendarEntry();
    
    void addAttendee(const XQCalendarAttendee& attendee);
    void addCategory(const XQCalendarCategory& category);
    
    bool setStartAndEndTime(const QDateTime& startTime, const QDateTime& endTime);
    QDateTime startTime() const;
    QDateTime endTime() const;
    
    QList<XQCalendarAttendee>& attendees();
    const QList<XQCalendarAttendee>& attendees() const;
    QList<XQCalendarCategory>& categories();
    const QList<XQCalendarCategory>& categories() const;
    
    void setDescription(const QString& description);
    QString description() const;
    
    void setType(Type type);
    Type type() const;
    
    void setAlarm(const XQCalendarAlarm& alarm);
    XQCalendarAlarm alarm() const;
    
    void setLocation(const QString& location);
    QString location() const;
    
    void setSummary(const QString& summary);
    QString summary() const;
    
    void setMethod(Method method);
    Method method() const;
    
    void setRepeatRule(const XQCalendarRepeatRule& repeatRule);
    XQCalendarRepeatRule repeatRule() const;
    
    void setPriority(int priority);
    int priority() const;
    
    bool isNull() const;

    ulong id() const;
    
    XQCalendarEntry& operator=(const XQCalendarEntry& other);
    bool operator==(const XQCalendarEntry& other) const;
    bool operator!=(const XQCalendarEntry& other) const;
    
private:
    void detach();

private:    
    XQCalendarEntryPrivate* d;
    friend class XQCalendarPrivate;
};

#endif // XQCALENDARENTRY_H

// End of file
