using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BabyFeed.Domain;

namespace BabyFeed.Provider
{
    public interface IDataService
    {
        Baby PersistBaby(Baby baby);
        void DeleteBaby(Baby baby);
        List<Baby> ListBabies();
        Event PersistEvent(Event evt);
        List<Event> ListEvents(Baby baby, DateTime startDate, DateTime endDate);
        List<Event> ListEvents(Baby baby, DateTime startDate, DateTime endDate, char eventType);
        List<Event> ListEvents(Baby baby, int offset, int count, char eventType);
        int CountEvents(Baby baby, char eventType);
        int CountEvents(Baby baby, char eventType, DateTime endDate);
        List<Event> ListFeedEvents(Baby baby, DateTime startDate, DateTime endDate);
        List<Event> ListFeedEvents(Baby baby, int offset, int count);
        int CountFeedingEvents(Baby baby);
        int CountFeedingEvents(Baby baby, DateTime endDate);
        DateTime CalcMinEventDate(Baby baby, char eventType);
        DateTime CalcMaxEventDate(Baby baby, char eventType);
        DateTime CalcMinFeedDate(Baby baby);
        DateTime CalcMaxFeedDate(Baby baby);
        Baby GetSelectedBaby();
        Baby GetBabyById(int id);
        Event GetLastMeasureEvent(Baby baby);
        void DeleteEvent(Event evt);
        List<BabyEventGroup> ListBabyEventGroups(int days);
        Event GetEventById(int id);
    }
}
