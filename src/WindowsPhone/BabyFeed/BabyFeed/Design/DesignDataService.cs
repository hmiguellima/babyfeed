using System;
using BabyFeed.Domain;
using System.Collections.Generic;
using BabyFeed.Provider;

namespace BabyFeed.Design
{
    public class DesignDataService : IDataService
    {

        public List<Baby> ListBabies()
        {
            List<Baby> babies = new List<Baby>();

            babies.Add(new Baby { Name = "Maria", Photo = "/Images/baby1.jpeg", BirthDate=new DateTime(2010, 7, 26)});
            babies.Add(new Baby { Name = "Pedro", Photo = "/Images/baby2.jpeg", BirthDate = new DateTime(2002, 1, 1) });
            babies.Add(new Baby { Name = "Barbara", Photo = "/Images/baby3.jpeg", BirthDate=new DateTime(2006, 8,  19)});
            babies.Add(new Baby { Name = "Samuel", Photo = "/Images/baby4.jpeg", BirthDate=new DateTime(2001, 1, 1)});
            babies.Add(new NoBaby());

            return babies;
        }


        public Baby GetBabyById(int id)
        {
            return new Baby { Name = "Maria", Photo = "/Images/baby1.jpeg" };
        }

        public List<Event> ListEvents(Baby baby, int offset, int count, char eventType)
        {
            List<Event> events = new List<Event>();
            Event evt;

            switch (eventType)
            {
                case Event.TYPE_POTTY:
                    evt = new PottyEvent();
                    evt.StartDate = DateTime.Now;
                    events.Add(evt);

                    break;
                case Event.TYPE_MEDICINE:
                    evt = new MedicineEvent();
                    evt.StartDate = DateTime.Now;
                    ((MedicineEvent)evt).MedicineName = "Amoxicilin";
                    evt.Notes = "2x Day";
                    events.Add(evt);

                    break;
                case Event.TYPE_MEASURE:
                    evt = new MeasureEvent();
                    evt.StartDate = DateTime.Now;
                    evt.Weight = 10099;
                    evt.Height = 10099;
                    evt.Cephalic = 10099;
                    events.Add(evt);

                    break;
                case Event.TYPE_NAP:
                    evt = new NapEvent();
                    evt.StartDate = DateTime.Now;
                    evt.Duration = 10;
                    events.Add(evt);

                    break;
            }

            return events;
        }
    
        public Baby  PersistBaby(Baby baby)
        {
 	        throw new NotImplementedException();
        }

        public void  DeleteBaby(Baby baby)
        {
 	        throw new NotImplementedException();
        }

        public Event  PersistEvent(Event evt)
        {
 	        throw new NotImplementedException();
        }

        public List<Event>  ListEvents(Baby baby, DateTime startDate, DateTime endDate)
        {
 	        throw new NotImplementedException();
        }

        public List<Event>  ListEvents(Baby baby, DateTime startDate, DateTime endDate, char eventType)
        {
 	        throw new NotImplementedException();
        }

        public int  CountEvents(Baby baby, char eventType)
        {
            switch (eventType)
            {
                case Event.TYPE_POTTY:
                    return 1;
                case Event.TYPE_MEDICINE:
                    return 1;
                case Event.TYPE_MEASURE:
                    return 100;
                case Event.TYPE_NAP:
                    return 2;
            }
            return 0;
        }

        public List<Event>  ListFeedEvents(Baby baby, DateTime startDate, DateTime endDate)
        {
 	        throw new NotImplementedException();
        }

        public DateTime  CalcMinEventDate(Baby baby, char eventType)
        {
 	        throw new NotImplementedException();
        }

        public DateTime  CalcMaxEventDate(Baby baby, char eventType)
        {
 	        throw new NotImplementedException();
        }

        public DateTime  CalcMinFeedDate(Baby baby)
        {
 	        throw new NotImplementedException();
        }

        public DateTime  CalcMaxFeedDate(Baby baby)
        {
 	        throw new NotImplementedException();
        }

        public Baby  GetSelectedBaby()
        {
 	        throw new NotImplementedException();
        }

        public Event  GetLastMeasureEvent(Baby baby)
        {
 	        throw new NotImplementedException();
        }

        public void  DeleteEvent(Event evt)
        {
 	        throw new NotImplementedException();
        }


        public List<Event> ListFeedEvents(Baby baby, int offset, int count)
        {
            List<Event> events=new List<Event>();
            Event evt;

            switch (offset)
            {
                case 0:
                    evt = new LFeedingEvent();
                    evt.StartDate = DateTime.Parse("2012-09-01");
                    evt.Checked = true;
                    events.Add(evt);
                    break;
                case 1:
                    evt = new RFeedingEvent();
                    evt.StartDate = DateTime.Parse("2012-10-15");
                    evt.Checked = false;
                    events.Add(evt);
                    break;
                case 2:
                    evt = new BFeedingEvent();
                    evt.StartDate = DateTime.Now;
                    evt.Checked = true;
                    events.Add(evt);
                    break;
            }

            return events;
        }

        public int CountFeedingEvents(Baby baby)
        {
            return 3;
        }


        public List<BabyEventGroup> ListBabyEventGroups(int days)
        {
            List<BabyEventGroup> eventGroups = new List<BabyEventGroup>();
            BabyEventGroup group;
            List<Event> events;
            Event evt;

            events = new List<Event>();
            evt = new LFeedingEvent();
            evt.StartDate = DateTime.Parse("2012-09-01");
            evt.Checked = true;
            events.Add(evt);
            group = new BabyEventGroup("Maria", events);

            eventGroups.Add(group);

            events = new List<Event>();
            evt = new RFeedingEvent();
            evt.StartDate = DateTime.Parse("2012-08-01");
            evt.Checked = true;
            events.Add(evt);
            group = new BabyEventGroup("Barbara", events);

            eventGroups.Add(group);

            return eventGroups;
        }


        public Event GetEventById(int id)
        {
            LFeedingEvent evt = new LFeedingEvent();

            evt.StartDate = DateTime.Now;
            evt.Duration = 10;
            evt.Notes = "teste";

            return evt;

        }


        public int CountEvents(Baby baby, char eventType, DateTime endDate)
        {
            return 1;
        }

        public int CountFeedingEvents(Baby baby, DateTime endDate)
        {
            return 1;
        }
    } 
}