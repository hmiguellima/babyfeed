#ifndef XQCALENDAR_P_H
#define XQCALENDAR_P_H

// INCLUDES
#include "xqcalendar.h"
#include <calsession.h>
#include <calprogresscallback.h>
#include <calrrule.h>
#include <calentry.h>
#include <calentryview.h>
#include <calalarm.h>
#include <calcategory.h>

// FORWARD DECLARATIONS
class CCalSession;

// CLASS DECLARATION
class XQCalendarPrivate: public CBase, public MCalProgressCallBack, MCalChangeCallBack2
{
public:
    XQCalendarPrivate(XQCalendar* calendar);
    ~XQCalendarPrivate();
    
    ulong addEntry(const XQCalendarEntry& entry);
    bool deleteEntry(ulong id);
    bool updateEntry(const XQCalendarEntry& entry);
    int importvCalendar(const QString& fileName);
    bool exportAsvCalendar(const QString& fileName,  ulong calendarEntryId);
    XQCalendarEntry fetchById(ulong ids);
    QList<ulong> entryIds(XQCalendar::FilterFlags filter);
    XQCalendar::Error error() const;
    
protected: // From MCalProgressCallBack
    void Progress(TInt /*aPercentageCompleted*/) {};
    void Completed(TInt aError);
    TBool NotifyProgress() {return EFalse;};

protected: // From MCalChangeCallback2
    void CalChangeNotification(RArray<TCalChangeEntry>& aChangeItems); 

private:
    bool addAttendeesToEntry(const QList<XQCalendarAttendee>& attendees, CCalEntry& entry);
    bool addCategoriesToEntry(const QList<XQCalendarCategory>& categories, CCalEntry& entry);
    bool setAlarmToEntry(const XQCalendarAlarm& alarm, CCalEntry& entry);
    bool prepareSession();
    
private:
    XQCalendar* q;
    CCalSession* iCalSession;
    CCalEntryView* iCalEntryView;    
    CActiveSchedulerWait* iWait;
    mutable int iError;
};

#endif /*XQCALENDAR_P_H*/

// End of file
