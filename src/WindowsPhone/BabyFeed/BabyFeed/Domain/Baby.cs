using System;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data.Linq.Mapping;
using BabyFeed.Provider;

namespace BabyFeed.Domain
{
    [Table]
    public class Baby
    {
        public enum Genders { Boy, Girl, NewBaby };

        [Column(IsPrimaryKey = true, IsDbGenerated = true, DbType = "INT NOT NULL Identity", CanBeNull = false, AutoSync = AutoSync.OnInsert)]
        public virtual int Id { get; set; }

        [Column]
        public virtual String Name { get; set; }

        [Column]
        public DateTime BirthDate { get; set; }

        [Column]
        public virtual Genders Gender { get; set; }

        [Column]
        public virtual bool Selected { get; set; }

        [Column]
        public bool FeedAlarmActive { get; set; }

        [Column]
        public int TimeBetweenFeeds { get; set; }

        [Column]
        public virtual string Photo { get; set; }

        public Baby Persist(IDataService data)
        {
            return data.PersistBaby(this);
        }

        public void Delete(IDataService data)
        {
            data.DeleteBaby(this);
        }

        public Baby PersistSelected(bool selected, IDataService data)
        {
            Selected = selected;
            return data.PersistBaby(this);
        }

        public List<Event> ListEvents(DateTime startDate, DateTime endDate, IDataService data)
        {
            return data.ListEvents(this, startDate, endDate); 
        }

        public List<Event> ListFeedEvents(DateTime startDate, DateTime endDate, IDataService data)
        {
            return data.ListFeedEvents(this, startDate, endDate);
        }

        public List<Event> ListMeasureEvents(DateTime startDate, DateTime endDate, IDataService data)
        {
            return data.ListEvents(this, startDate, endDate, Event.TYPE_MEASURE);
        }

        public Event GetLastMeasureEvent(IDataService data)
        {
            return data.GetLastMeasureEvent(this);
        }

        public virtual String Age
        {
            get
            {
                DateTime today = DateTime.Now;
                int months = 0;
                int weeks;
                int days;


                months = (today.Year - BirthDate.Year) * 12 + (today.Month - BirthDate.Month);

                if ((today.Day < BirthDate.Day))
                    months--;

                if (months > 0)
                {
                    if (months < 12)
                        return String.Format(AppResx.agemonths, months);
                    else
                        if (months % 12 == 0)
                            return String.Format(AppResx.ageyears, months / 12);
                        else
                            return String.Format(AppResx.ageyearsmonths, months / 12, months % 12);
                }
                else
                {
                    today = DateTime.Now;

                    days = today.Subtract(BirthDate).Days;
                    weeks = days / 7;
                    if (weeks > 0)
                        return String.Format(AppResx.ageweeksdays, weeks, days % 7);
                    else
                        return String.Format(AppResx.agedays, days);
                }
            }
        }

        public DateTime CalcMinFeedEventDate(IDataService data)
        {
            return data.CalcMinFeedDate(this);
        }

        public DateTime CalcMaxFeedEventDate(IDataService data)
        {
            return data.CalcMaxFeedDate(this);
        }

        public DateTime CalcMinMeasurementEventDate(IDataService data)
        {
            return data.CalcMinEventDate(this, Event.TYPE_MEASURE);
        }

        public DateTime CalcMaxMeasurementEventDate(IDataService data)
        {
            return data.CalcMaxEventDate(this, Event.TYPE_MEASURE);
        }

        public void ExportEvents(String email, IEmailService emailService, Action<Exception> callback)
        {
        }

        public static List<Baby> List(IDataService data)
        {
            return data.ListBabies();
        }

        public static Baby GetBabyById(int id, IDataService data)
        {
            return data.GetBabyById(id);
        }

        public static bool BabyHasPhoto(Baby baby)
        {
            return false;
        }

        public static String GetBabyPhotoFileName(Baby baby)
        {
            return null;
        }

        public static String GetBabyPhotoUri(Baby baby)
        {
            return null;
        }

    }
}
