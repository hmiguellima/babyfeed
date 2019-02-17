using System;
using System.Data.Linq;
using System.Collections.Generic;
using System.Linq;
using BabyFeed.Domain;

namespace BabyFeed.Provider
{
    public class SqlDataService : DataContext, IDataService
    {
        private static string _connectionString = "Data Source=isostore:/babyfeed.sdf";

        private Table<Baby> Babies
        {
            get
            {
                return GetTable<Baby>();
            }
        }

        private Table<Event> Events
        {
            get
            {
                return GetTable<Event>();
            }
        }

        public SqlDataService() : base(_connectionString)
        {
            if (!DatabaseExists())
                CreateDatabase();
        }

        Baby IDataService.PersistBaby(Baby baby)
        {
            try
            {
                if (baby.Id == 0)
                    Babies.InsertOnSubmit(baby);

                SubmitChanges();
                return baby;
            }
            catch (Exception ex)
            {
                throw ex;
            }

        }


        List<Baby> IDataService.ListBabies()
        {
            List<Baby> babies;

            try
            {
                babies = (from Baby baby in Babies
                          orderby baby.Name
                          select baby).ToList<Baby>();
                babies.Add(new NoBaby());

                return babies;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        Event IDataService.PersistEvent(Event evt)
        {
            try
            {
                if (evt.Id==0)
                    Events.InsertOnSubmit(evt);
                SubmitChanges();
                return evt;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        void IDataService.DeleteBaby(Baby baby)
        {
            try
            {
                Babies.DeleteOnSubmit(baby);
                SubmitChanges();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        List<Event> IDataService.ListEvents(Baby baby, DateTime startDate, DateTime endDate)
        {
            List<Event> events;

            try
            {
                events = (from Event evt in Events
                          where ( (evt.BabyId == baby.Id) && (evt.StartDate>=startDate) && (evt.StartDate<=endDate) )
                          orderby evt.StartDate descending
                          select evt).ToList<Event>();

                return events;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        List<Event> IDataService.ListEvents(Baby baby, DateTime startDate, DateTime endDate, char eventType)
        {
            List<Event> events;

            try
            {
                events = (from Event evt in Events
                          where ((evt.BabyId == baby.Id) && (evt.StartDate >= startDate) && (evt.StartDate <= endDate) && (evt.Type==eventType))
                          orderby evt.StartDate descending
                          select evt).ToList<Event>();

                return events;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private DateTime CalcMinMaxEventDate(Baby baby, char[] eventTypes, bool min)
        {
            IQueryable<Event> events;

            if (min)
                events = (from Event evt in Events
                          where ((evt.BabyId == baby.Id) && (eventTypes.Contains(evt.Type)))
                          orderby evt.StartDate ascending
                          select evt);
            else
                events = (from Event evt in Events
                          where ((evt.BabyId == baby.Id) && (eventTypes.Contains(evt.Type)))
                          orderby evt.StartDate descending
                          select evt);

            foreach (Event evt in events)
            {
                return evt.StartDate;
            }

            return new DateTime();
        }

        private DateTime CalcMinMaxEventDate(Baby baby, char eventType, bool min)
        {
            return CalcMinMaxEventDate(baby, new[] { eventType }, min);
        }


        DateTime IDataService.CalcMinEventDate(Baby baby, char eventType)
        {

            try
            {
                return CalcMinMaxEventDate(baby, eventType, true);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        DateTime IDataService.CalcMaxEventDate(Baby baby, char eventType)
        {

            try
            {
                return CalcMinMaxEventDate(baby, eventType, false);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        public Baby GetSelectedBaby()
        {
            try
            {
                Baby selectedBaby;

                selectedBaby = (from Baby baby in Babies
                                where (baby.Selected == true)
                                select baby).SingleOrDefault<Baby>();

                return selectedBaby;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        public Baby GetBabyById(int id)
        {
            try
            {
                Baby selectedBaby;

                selectedBaby = (from Baby baby in Babies
                                where (baby.Id == id)
                                select baby).SingleOrDefault<Baby>();

                return selectedBaby;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        public List<Event> ListFeedEvents(Baby baby, DateTime startDate, DateTime endDate)
        {
            List<Event> events;

            try
            {
                events = (from Event evt in Events
                          where ((evt.BabyId == baby.Id) && (evt.StartDate >= startDate) && (evt.StartDate <= endDate) && (new[] {Event.TYPE_LEFT_BREAST, Event.TYPE_RIGHT_BREAST, Event.TYPE_BOTTLE}.Contains(evt.Type) ) )
                          orderby evt.StartDate descending
                          select evt).ToList<Event>();

                return events;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        public Event GetLastMeasureEvent(Baby baby)
        {
            Event lastEvent;

            try
            {
                lastEvent = (from Event evt in Events
                          where ((evt.BabyId == baby.Id) && (evt.Type==Event.TYPE_MEASURE))
                          orderby evt.StartDate descending
                          select evt).SingleOrDefault();

                return lastEvent;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        public void DeleteEvent(Event evt)
        {
            try
            {
                Events.DeleteOnSubmit(evt);
                SubmitChanges();
            }
            catch (Exception ex)
            {
                throw ex;
            }
       }


        public DateTime CalcMinFeedDate(Baby baby)
        {
            try
            {
                return CalcMinMaxEventDate(baby, new[]{Event.TYPE_BOTTLE, Event.TYPE_LEFT_BREAST, Event.TYPE_RIGHT_BREAST}, true);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public DateTime CalcMaxFeedDate(Baby baby)
        {
            try
            {
                return CalcMinMaxEventDate(baby, new[] { Event.TYPE_BOTTLE, Event.TYPE_LEFT_BREAST, Event.TYPE_RIGHT_BREAST }, false);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        public List<Event> ListEvents(Baby baby, int offset, int count, char eventType)
        {
            List<Event> events;

            try
            {
                events = (from Event evt in Events
                          where ((evt.BabyId == baby.Id) && (evt.Type == eventType))
                          orderby evt.StartDate descending
                          select evt).Skip(offset).Take(count).ToList<Event>();

                return events;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public int CountEvents(Baby baby, char eventType)
        {
            int count;

            try
            {
                count = (from Event evt in Events
                         where ((evt.BabyId == baby.Id) && (evt.Type == eventType))
                         select evt).Count();

                return count;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public List<Event> ListFeedEvents(Baby baby, int offset, int count)
        {
            List<Event> events;

            try
            {
                events = (from Event evt in Events
                          where ((evt.BabyId == baby.Id) && (new[] { Event.TYPE_LEFT_BREAST, Event.TYPE_RIGHT_BREAST, Event.TYPE_BOTTLE }.Contains(evt.Type)))
                          orderby evt.StartDate descending
                          select evt).Skip(offset).Take(count).ToList<Event>();

                return events;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public int CountFeedingEvents(Baby baby)
        {
            int count;

            try
            {
                count = (from Event evt in Events
                         where ((evt.BabyId == baby.Id) && (new[] { Event.TYPE_LEFT_BREAST, Event.TYPE_RIGHT_BREAST, Event.TYPE_BOTTLE }.Contains(evt.Type)))
                         select evt).Count();

                return count;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public List<BabyEventGroup> ListBabyEventGroups(int days)
        {
            return (from evt in Events
                    join baby in Babies on evt.BabyId equals baby.Id
                    where evt.StartDate.AddDays(-days) >= DateTime.Now
                    group evt by baby.Name into babyevents
                    orderby babyevents.Key
                    select new BabyEventGroup(babyevents.Key, babyevents)).ToList();
        }


        public Event GetEventById(int id)
        {
            return (from Event evt in Events
                    where evt.Id == id
                    select evt).First();
        }
    

        public int  CountEvents(Baby baby, char eventType, DateTime endDate)
        {
            int count;

            try
            {
                count = (from Event evt in Events
                         where ((evt.BabyId == baby.Id) && (evt.Type == eventType) && (evt.StartDate <= endDate))
                         orderby evt.StartDate descending
                         select evt).Count();

                return count;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        public int CountFeedingEvents(Baby baby, DateTime endDate)
        {
            int count;

            try
            {
                count = (from Event evt in Events
                         where ((evt.BabyId == baby.Id) && (new[] { Event.TYPE_LEFT_BREAST, Event.TYPE_RIGHT_BREAST, Event.TYPE_BOTTLE }.Contains(evt.Type)) && (evt.StartDate <= endDate))
                         orderby evt.StartDate descending
                         select evt).Count();

                return count;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}