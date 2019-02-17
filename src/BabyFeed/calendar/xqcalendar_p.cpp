#include "xqcalendar_p.h"
#include "xqcalendarentry.h"
#include "xqcalendarentry_p.h"

#include <calsession.h>
#include <calinstance.h>
#include <calentry.h>
#include <e32math.h>
#include <caluser.h>
#include <calinstanceview.h>
#include <caldataexchange.h>
#include <caldataformat.h>
#include <f32file.h>
#include <s32file.h>
#include <asshddefs.h> 

const TInt KGuidLength = 30;
static const int startDateArray[2] = { 1900, 1};
static const int endDateArray[2] = { 2100, 1};

XQCalendarPrivate::XQCalendarPrivate(XQCalendar* calendar)
    : q(calendar)
{       
}

bool XQCalendarPrivate::prepareSession()
{
    if (!iCalSession)
    {
        TRAP(iError, iCalSession = CCalSession::NewL();)   
        if (!iCalSession)
        {  
            return false;
        }
        const TDesC& file = iCalSession->DefaultFileNameL(); 
        TRAPD(iError, iCalSession->OpenL(file));
        if(iError == KErrNotFound)
        {
                iCalSession->CreateCalFileL(file);
                iCalSession->OpenL(file);   
        }
        else if (iError != KErrNone)
        {
            return false;
        }    
        
        TCalTime startDateForInstanceSearch;
        TCalTime endDateForInstanceSearch;
        
        TDateTime startTime = TDateTime(
                startDateArray[0], 
                static_cast<TMonth>(startDateArray[1]), 
                0,
                0, 
                0, 
                0, 
                0);
        
        TDateTime endTime = TDateTime(
                endDateArray[0], 
                static_cast<TMonth>(endDateArray[1]), 
                0,
                0, 
                0, 
                0, 
                0);
        
        startDateForInstanceSearch.SetTimeLocalL(startTime);
        endDateForInstanceSearch.SetTimeLocalL(endTime);
        CalCommon::TCalTimeRange searchTimeRange(
                startDateForInstanceSearch, endDateForInstanceSearch);
        
        CCalChangeNotificationFilter* filter = CCalChangeNotificationFilter::NewL(
                EChangeEntryAll, 
                true,
                searchTimeRange);
        
        iCalSession->StartChangeNotification(*this, *filter);
        delete filter;
    }    
    if (!iWait)
    {
        TRAP(iError, iWait = new (ELeave) CActiveSchedulerWait;)
        if (iError != KErrNone)
        {
            return false;
        }
    }
    
    if (!iCalEntryView)
    {
        TRAP(iError, iCalEntryView = CCalEntryView::NewL(*iCalSession, *this);) 
        
        if( !iWait->IsStarted() )
        {
            iWait->Start();
        }
        else
        {
            iError = KErrInUse;
            return false;
        }
    }  
    return true;
}

XQCalendarPrivate::~XQCalendarPrivate()
{
    delete iCalEntryView;
    if (iWait && iWait->IsStarted())
    {
        iWait->AsyncStop();
    }

    delete iWait;
    if (iCalSession)
    {
        iCalSession->StopChangeNotification();
    }
    delete iCalSession;
}

void XQCalendarPrivate::Completed(TInt aError)
{
    iError = aError;
    if (iCalEntryView)
    {       
        if (iWait->IsStarted())
        {
            iWait->AsyncStop();
        }
        else
        {
            iError = KErrInUse;
        }        
    }
}

void XQCalendarPrivate::CalChangeNotification(RArray<TCalChangeEntry>& aChangeItems)
{
    QList<ulong> ids;
    for (int i = 0; i < aChangeItems.Count(); i++)
    {
        ids.append(aChangeItems[i].iEntryId);
    }
    emit q->entriesChanged(ids);
}

ulong XQCalendarPrivate::addEntry(const XQCalendarEntry& entry)
{
    prepareSession();
    TCalLocalUid localUid = 0;
    TRAP(iError,
        RPointerArray<CCalEntry> array;
        CleanupClosePushL(array);
        
        TTime now;
        now.HomeTime();
        TInt64 seed = now.Int64();
        TInt randNum = Math::Rand(seed);
        HBufC8* guid = HBufC8::NewLC(KGuidLength);
        guid->Des().Num(randNum);        
        
        CCalEntry* currentEntry = CCalEntry::NewL(
                static_cast<CCalEntry::TType>(entry.type()),
                guid, 
                static_cast<CCalEntry::TMethod>(entry.method()), 
                0);
        
        CleanupStack::Pop(guid); 
        CleanupStack::PushL(currentEntry);
        
        // Summary
        if (!entry.summary().isNull())
        {
            TPtrC summary(reinterpret_cast<const TUint16*>(entry.summary().utf16()));
            currentEntry->SetSummaryL(summary);
        }
        
        // Date and time
        QDateTime startDateTime = entry.startTime();
        QDate startDate = startDateTime.date();
        QTime startTime = startDateTime.time();
        
        TDateTime startCalendarDateTime(
                startDate.year(), 
                static_cast<TMonth>(startDate.month()-1),
                startDate.day()-1, 
                startTime.hour(), 
                startTime.minute(), 
                0, 
                0);
            
        TTime startCalTime(startCalendarDateTime);
        TCalTime calTime;
        calTime.SetTimeLocalL(startCalTime);
        QDateTime endDateTime = entry.endTime();
        QDate endDate = endDateTime.date();
        QTime endTime = endDateTime.time();
      
        TDateTime endCalendarDateTime(
                endDate.year(), 
                static_cast<TMonth>(endDate.month()-1), 
                endDate.day()-1, 
                endTime.hour(), 
                endTime.minute(), 
                0, 
                0);
        
        TTime endCalTime(endCalendarDateTime);
        TCalTime calTime2;
        calTime2.SetTimeLocalL(endCalTime);
        
        currentEntry->SetStartAndEndTimeL(calTime, calTime2);  
        
        // Calendar attendee
        addAttendeesToEntry(entry.d->m_attendees, *currentEntry);    

        // Categories
        addCategoriesToEntry(entry.d->m_categories, *currentEntry);
        
        // Description
        TPtrC description(reinterpret_cast<const TUint16*>(entry.description().utf16()));
        currentEntry->SetDescriptionL(description);
        
        // Alarm
        XQCalendarAlarm alarm = entry.alarm();
        if (!alarm.isNull())
        {
            setAlarmToEntry(alarm, *currentEntry);    
        }
        
        // Priority
        int priority = entry.priority();
        if (entry.priority() != -1)
        {
            currentEntry->SetPriorityL(priority);
        }
        
        // Location
        if (!entry.location().isNull())
        {
            TPtrC location(reinterpret_cast<const TUint16*>(entry.location().utf16()));
            currentEntry->SetLocationL(location);
        }
        
        array.AppendL(currentEntry);
        TInt success(0);
        iCalEntryView->StoreL(array, success);
        localUid = currentEntry->LocalUidL();
        CleanupStack::Pop(currentEntry);
        CleanupStack::PopAndDestroy(&array);
    )
    
    return localUid;
}

bool XQCalendarPrivate::deleteEntry(ulong id)
{
    prepareSession();
    TInt success = 0;
    TRAP(iError,
        RArray<TCalLocalUid> uids;
        CleanupClosePushL(uids);
    
        uids.AppendL(id);
        iCalEntryView->DeleteL(uids, success);
        CleanupStack::PopAndDestroy(&uids);
    )
    return (success != 0);
}

bool XQCalendarPrivate::updateEntry(const XQCalendarEntry& entry)
{
    prepareSession();
    TInt success = 0;   
    
    TRAP(iError,
        XQCalendarEntry storedEntry = fetchById(entry.id());
        CCalEntry* calEntry = iCalEntryView->FetchL(entry.id());
        CleanupStack::PushL(calEntry);
        
        // Attendees
        if (!entry.isNull() && (entry.d->m_attendees != storedEntry.attendees()))
        {
            RPointerArray<CCalAttendee> attendeesArray = calEntry->AttendeesL();
            CleanupClosePushL(attendeesArray);
            int i = 0;
            while (attendeesArray.Count() > i)
            {
                calEntry->DeleteAttendeeL(i);     
                i++;
            }
                
            CleanupStack::PopAndDestroy(&attendeesArray);
            
            addAttendeesToEntry(entry.d->m_attendees, *calEntry);    
        }
            
        // Categories
        if (entry.d->m_categories != storedEntry.categories())
        {
            RPointerArray<CCalCategory> categories = calEntry->CategoryListL();
            CleanupClosePushL(categories);
            int i = 0;
            while (categories.Count() > i)
            {
                calEntry->DeleteAttendeeL(i);     
                i++;
            }
            CleanupStack::PopAndDestroy(&categories);
            
            addCategoriesToEntry(entry.d->m_categories, *calEntry);
        }
        
        // Alarm
        if (entry.alarm() != storedEntry.alarm())
        {
           setAlarmToEntry(entry.alarm(), *calEntry);    
        }
        
        
        if (storedEntry.description() != entry.description() && !entry.description().isNull())
        {
            calEntry->SetDescriptionL(
                    TPtrC(reinterpret_cast<const TUint16*>(entry.description().utf16())));
        }
        
        if (storedEntry.location() != entry.location() && !entry.location().isNull())
        {
            calEntry->SetLocationL(
                    TPtrC(reinterpret_cast<const TUint16*>(entry.location().utf16())));
        }
        
        if (storedEntry.priority() != entry.priority() && entry.priority() != -1)
        {
            calEntry->SetPriorityL(entry.priority());
        }
        
        if (storedEntry.summary() != entry.summary() && !entry.summary().isNull())
        {
            calEntry->SetSummaryL(
                    TPtrC(reinterpret_cast<const TUint16*>(entry.summary().utf16())));
        }
        
        if (storedEntry.method() != entry.method() && 
            entry.method() != XQCalendarEntry::MethodUnknown)
        {
            calEntry->SetMethodL(static_cast<CCalEntry::TMethod>(entry.method()));            
        }
        
        if (storedEntry.startTime() != entry.startTime() || 
            storedEntry.endTime() != entry.endTime())
        {
            QDateTime startDateTime = entry.startTime();
            QDate startDate = startDateTime.date();
            QTime startTime = startDateTime.time();
            
            TDateTime startCalendarDateTime(
                    startDate.year(), 
                    static_cast<TMonth>(startDate.month()-1), 
                    startDate.day()-1, 
                    startTime.hour(), 
                    startTime.minute(), 
                    0, 
                    0);
                
            TTime startCalTime(startCalendarDateTime);
            TCalTime calTime;
            calTime.SetTimeLocalL(startCalTime);
            QDateTime endDateTime = entry.endTime();
            QDate endDate = endDateTime.date();
            QTime endTime = endDateTime.time();
          
            TDateTime endCalendarDateTime(
                    endDate.year(),
                    static_cast<TMonth>(endDate.month()-1), 
                    endDate.day()-1, 
                    endTime.hour(), 
                    endTime.minute(), 
                    0, 
                    0);
            
            TTime endCalTime(endCalendarDateTime);
            TCalTime calTime2;
            calTime2.SetTimeLocalL(endCalTime);
            
            calEntry->SetStartAndEndTimeL(calTime, calTime2);  
        }
        
        RPointerArray<CCalEntry> array;
        CleanupClosePushL(array);
    
        iCalEntryView->UpdateL(array, success);
        
        CleanupStack::PopAndDestroy(2, calEntry);
    )
    
    return (success != 0);
}

XQCalendarEntry XQCalendarPrivate::fetchById(ulong id)
{
    prepareSession();
    XQCalendarEntry entry;
    TRAP(iError,
        CCalEntry* calEntry = iCalEntryView->FetchL(id);
        CleanupStack::PushL(calEntry);
        
        // Type
        XQCalendarEntry::Type entryType = 
            static_cast<XQCalendarEntry::Type>(calEntry->EntryTypeL());
        entry.setType(entryType);
        
        // Method
        XQCalendarEntry::Method method = 
            static_cast<XQCalendarEntry::Method>(calEntry->MethodL());
        entry.setMethod(method);
        
        // Summary
        TPtrC calSummary = calEntry->SummaryL();
        entry.setSummary(QString::fromUtf16(calSummary.Ptr(), calSummary.Length()));
        
        // Description
        TPtrC calDescription = calEntry->DescriptionL();
        entry.setDescription(QString::fromUtf16(calDescription.Ptr(), calDescription.Length()));
        
        // Location
        TPtrC calLocation = calEntry->LocationL();
        entry.setLocation(QString::fromUtf16(calLocation.Ptr(), calLocation.Length()));
        
        // Priority
        entry.setPriority(calEntry->PriorityL());
        
        // Time
        TDateTime calStartDateTime = calEntry->StartTimeL().TimeLocalL().DateTime();
        QDateTime startDateTime(
                QDate(calStartDateTime.Year(), 
                calStartDateTime.Month()+1, 
                calStartDateTime.Day()+1), 
                QTime(calStartDateTime.Hour(), 
                calStartDateTime.Minute(), 
                0, 
                0));
        
        TDateTime calEndDateTime = calEntry->EndTimeL().TimeLocalL().DateTime();
        QDateTime endDateTime(
                QDate(calEndDateTime.Year(), 
                calEndDateTime.Month()+1, 
                calEndDateTime.Day()+1), 
                QTime(calEndDateTime.Hour(), 
                calEndDateTime.Minute(), 
                0,
                0));
        
        entry.setStartAndEndTime(startDateTime, endDateTime);
        
        // Attendees
        RPointerArray<CCalAttendee> calAttendees = calEntry->AttendeesL();
        CleanupClosePushL(calAttendees);
        
        for (int i = 0; i < calAttendees.Count(); i++)
        {
            XQCalendarAttendee attendee;
            // Address
            TPtrC calAddress = calAttendees[i]->Address();
            attendee.setAddress(QString::fromUtf16(calAddress.Ptr(), calAddress.Length()));
            
            // Common name
            TPtrC calCommonName = calAttendees[i]->CommonName();
            attendee.setCommonName(
                    QString::fromUtf16(calCommonName.Ptr(), calCommonName.Length()));
            
            // Response requested
            attendee.setResponseRequested(calAttendees[i]->ResponseRequested());
            
            // Participant role
            attendee.setRole(
                    static_cast<XQCalendarAttendee::ParticipantRole>(calAttendees[i]->RoleL()));
    
            // Status
            attendee.setStatus(
                    static_cast<XQCalendarAttendee::StatusType>(calAttendees[i]->StatusL()));
            entry.addAttendee(attendee);
        }
        CleanupStack::Pop(&calAttendees);
        
        // Categories
        RPointerArray<CCalCategory> calCategories = calEntry->CategoryListL();
        CleanupClosePushL(calCategories);
         
        for (int i = 0; i < calCategories.Count(); i++)
        {
            XQCalendarCategory category;
            CCalCategory::TCalCategoryType categoryType = calCategories[i]->Category();
            if (categoryType == CCalCategory::ECalExtended)
            {
                TPtrC categoryName = calCategories[i]->ExtendedCategoryName();
                category.setExtendedCategoryName(
                        QString::fromUtf16(categoryName.Ptr(), categoryName.Length()));
            }
            category.setCategory(static_cast<XQCalendarCategory::CategoryType>(categoryType));
            entry.addCategory(category);
        }
        CleanupStack::Pop(&calCategories);
        
        // Id
        entry.d->m_id = id;
    
        // Alarm
        CCalAlarm* calAlarm = calEntry->AlarmL();
        if (calAlarm)
        {
            CleanupStack::PushL(calAlarm);
            XQCalendarAlarm alarm;
            alarm.setAlarmSoundName(QString::fromUtf16(
                    calAlarm->AlarmSoundNameL().Ptr(), 
                    calAlarm->AlarmSoundNameL().Length()));
            alarm.setTimeOffset(calAlarm->TimeOffset().Int());
            entry.setAlarm(alarm);     
            CleanupStack::PopAndDestroy(calAlarm);
        }
        
        CleanupStack::PopAndDestroy(calEntry);
    )
    
    return entry;
}

QList<ulong> XQCalendarPrivate::entryIds(XQCalendar::FilterFlags filter)
{
    prepareSession();
    QList<ulong> listOfIds;
    TRAP(iError,
        CCalInstanceView* instanceView = CCalInstanceView::NewL(*iCalSession, *this);
        CleanupStack::PushL(instanceView);
    
        if(!iWait->IsStarted())
        {
            iWait->Start();
        }
        else
        {
            iError = KErrInUse;
            return QList<ulong>();
        }
        
        RPointerArray<CCalInstance> instanceList;
        CleanupClosePushL(instanceList);
        CalCommon::TCalViewFilter filters = filter;
        TCalTime startDateForInstanceSearch;
        TCalTime endDateForInstanceSearch;
        
        TDateTime startTime = TDateTime(
                startDateArray[0], 
                static_cast<TMonth>(startDateArray[1]), 
                0,
                0, 
                0, 
                0, 
                0);
        
        TDateTime endTime = TDateTime(
                endDateArray[0], 
                static_cast<TMonth>(endDateArray[1]), 
                0,
                0, 
                0, 
                0, 
                0);
        
        startDateForInstanceSearch.SetTimeLocalL(startTime);
        endDateForInstanceSearch.SetTimeLocalL(endTime);
        CalCommon::TCalTimeRange searchTimeRange(
                startDateForInstanceSearch, 
                endDateForInstanceSearch);
        
        instanceView->FindInstanceL(instanceList, filters, searchTimeRange);
            
        TDateTime date; 
        
        for(TInt i = 0; i<instanceList.Count(); i++)
        {
            listOfIds.append(instanceList[i]->Entry().LocalUidL());
        }
            
        CleanupStack::PopAndDestroy(2, instanceView); 
    )

    return listOfIds;
}

int XQCalendarPrivate::importvCalendar(const QString& fileName)
{
    prepareSession();
    TInt success(0);
    TRAP(iError,
        RFs fs;
        User::LeaveIfError(fs.Connect());
        CleanupClosePushL(fs);
        TPtrC path(reinterpret_cast<const TUint16*>(fileName.utf16()));
        RFileReadStream rs;
        User::LeaveIfError(rs.Open(fs, path, EFileRead));
        CleanupClosePushL(rs);
    
        RPointerArray<CCalEntry> calEntryArray;
        CleanupClosePushL(calEntryArray);
        CCalDataExchange* calDataExchange = CCalDataExchange::NewL(*iCalSession);
        CleanupStack::PushL(calDataExchange);
        calDataExchange->ImportL(KUidVCalendar, rs, calEntryArray);
        iCalEntryView->StoreL(calEntryArray, success);
        
        CleanupStack::Pop(4, &fs);
    )
  
    return success;
}

bool XQCalendarPrivate::exportAsvCalendar(const QString& fileName, ulong calendarEntryId)
{
prepareSession();
   TRAP(iError,
        TPtrC path(reinterpret_cast<const TUint16*>(fileName.utf16()));
        RFs fs;
        User::LeaveIfError(fs.Connect());
        CleanupClosePushL(fs);
        fs.MkDirAll(path);
        RFileWriteStream rs;
        User::LeaveIfError(rs.Replace(fs, path, EFileWrite));
    
        CCalEntry* entry = iCalEntryView->FetchL(calendarEntryId);
        CleanupStack::PushL(entry);
    
        RPointerArray<CCalEntry> calEntryArray;
        CleanupClosePushL(calEntryArray);
        CCalDataExchange* calDataExchange = CCalDataExchange::NewL(*iCalSession);
        CleanupStack::PushL(calDataExchange); 
        calDataExchange->ExportL(KUidVCalendar, rs, calEntryArray);
        
        CleanupStack::PopAndDestroy(4, &fs);
   )
    
    return (iError == KErrNone);
}

XQCalendar::Error XQCalendarPrivate::error() const
{
    switch (iError) 
    {
        case KErrNone:
            return XQCalendar::NoError;
        case KErrNoMemory:
            return XQCalendar::OutOfMemoryError;
        case KErrInUse:
            return XQCalendar::AlreadyInUse;
        default:
            return XQCalendar::UnknownError;
    }
}

bool XQCalendarPrivate::addAttendeesToEntry(
     const QList<XQCalendarAttendee>& attendees, CCalEntry& entry)
{
    prepareSession();
    TRAP(iError,
        for (int i = 0; i < attendees.count(); i++)
        {
            CCalAttendee* attendee = CCalAttendee::NewL(
                    TPtrC(reinterpret_cast<const TUint16*>(attendees.at(i).address().utf16())));
            CleanupStack::PushL(attendee);
            attendee->SetCommonNameL(
                    TPtrC(reinterpret_cast<const TUint16*>(attendees.at(i).commonName().utf16())));
            attendee->SetResponseRequested(attendees.at(i).responseRequested());
            attendee->SetRoleL(static_cast<CCalAttendee::TCalRole>(attendees.at(i).role()));
            attendee->SetStatusL(static_cast<CCalAttendee::TCalStatus>(attendees.at(i).status()));
            entry.AddAttendeeL(attendee);
            CleanupStack::PopAndDestroy(attendee);
        } 
    )
    return (iError == KErrNone);
}

bool XQCalendarPrivate::addCategoriesToEntry(
    const QList<XQCalendarCategory>& categories, CCalEntry& entry)
{
    prepareSession();
    TRAP(iError,
        for (int i = 0; i < categories.count(); i++)
        {
            XQCalendarCategory::CategoryType type = categories.at(i).category();
            if (type != XQCalendarCategory::ExtendedCategory)
            {
                CCalCategory* category = CCalCategory::NewL(
                        static_cast<CCalCategory::TCalCategoryType>(type));  
                entry.AddCategoryL(category);
                delete category;
            }
            else
            {
                TPtrC categoryName = TPtrC(reinterpret_cast<const TUint16*>(
                        categories.at(i).extendedCategoryName().utf16()));
                CCalCategory* category = CCalCategory::NewL(categoryName);
                entry.AddCategoryL(category);
                delete category;
            }

        } 
    )
    return (iError == KErrNone);   
}

bool XQCalendarPrivate::setAlarmToEntry(const XQCalendarAlarm& alarm, CCalEntry& entry)
{
    TRAP(iError,
        if (alarm.isNull())
        {
            entry.SetAlarmL(0); 
        }
        else
        {
            CCalAlarm* calAlarm = CCalAlarm::NewL();
            CleanupStack::PushL(calAlarm);
            calAlarm->SetTimeOffset(alarm.timeOffset());
            if (!alarm.alarmSoundName().isNull())
            {
                TPtrC alarmName(reinterpret_cast<const TUint16*>(alarm.alarmSoundName().utf16()));
                calAlarm->SetAlarmSoundNameL(alarmName);
            }
            entry.SetAlarmL(calAlarm);
            CleanupStack::PopAndDestroy(calAlarm);
        }
    )
    return (iError == KErrNone);
}


// End of file
