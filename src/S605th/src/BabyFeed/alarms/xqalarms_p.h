#ifndef XQALARMS_P_H
#define XQALARMS_P_H

// INCLUDES
#include <ASCliSession.h>
#include <ASShdAlarm.h>
#include <ASShdDefs.h>
#include "xqalarms.h"

// CLASS DECLARATION
class XQAlarmsPrivate : public CBase
{
public:
    XQAlarmsPrivate(XQAlarms *qq);
    ~XQAlarmsPrivate();
    
public:
    XQAlarm alarm(int alarmId) const;
    QList<int> alarmIds() const;

    bool addAlarm(XQAlarm& alarmData);
    bool deleteAlarm(int alarmId);
    
    bool setEnabled(int alarmId, bool status);
    bool isEnabled(int alarmId) const;
    
    XQAlarms::Error error() const;
    
private:
    XQAlarms *q;
    RASCliSession iSession;
    
    mutable int iError;
};

#endif /*XQALARMS_P_H*/

// End of file
