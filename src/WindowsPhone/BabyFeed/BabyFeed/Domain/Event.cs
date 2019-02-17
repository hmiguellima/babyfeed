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
using System.Data.Linq.Mapping;
using BabyFeed.Provider;

namespace BabyFeed.Domain
{
    [Table]
    [InheritanceMapping(Code = TYPE_LEFT_BREAST, Type = typeof(LFeedingEvent), IsDefault=true)]
    [InheritanceMapping(Code = TYPE_BOTTLE, Type = typeof(BFeedingEvent))]
    [InheritanceMapping(Code = TYPE_RIGHT_BREAST, Type = typeof(RFeedingEvent))]
    [InheritanceMapping(Code = TYPE_MEDICINE, Type = typeof(MedicineEvent))]
    [InheritanceMapping(Code = TYPE_POTTY, Type = typeof(PottyEvent))]
    [InheritanceMapping(Code = TYPE_MEASURE, Type = typeof(MeasureEvent))]
    [InheritanceMapping(Code = TYPE_NAP, Type = typeof(NapEvent))]
    public abstract class Event
    {
        public const char TYPE_LEFT_BREAST = 'L';
        public const char TYPE_BOTTLE = 'B';
        public const char TYPE_RIGHT_BREAST = 'R';
        public const char TYPE_MEDICINE = 'M';
        public const char TYPE_POTTY = 'P';
        public const char TYPE_MEASURE = 'W';
        public const char TYPE_NAP = 'N';

        [Column(IsPrimaryKey = true, IsDbGenerated = true, DbType = "INT NOT NULL Identity", CanBeNull = false, AutoSync = AutoSync.OnInsert)]
        public int Id { get; set; }

        [Column]
        public int BabyId { get; set; }

        [Column]
        public int RecurrenceId { get; set; }

        [Column]
        public int AlarmNativeId { get; set; }

        [Column]
        public String AlarmNativeKey { get; set; }

        [Column]
        public bool Checked { get; set; }

        [Column]
        public int Duration { get; set; }

        [Column]
        public DateTime StartDate { get; set; }

        [Column]
        public int Height { get; set; }

        [Column]
        public int Weight { get; set; }

        [Column]
        public int Cephalic { get; set; }

        [Column]
        public virtual String Notes { get; set; }

        public abstract String Icon { get; }

        public abstract String ShortDesc { get; }

        public abstract String AlarmDesc { get; }

        [Column]
        public virtual bool Empty { get; set;  }

        public abstract bool Recurrentable { get; }

        [Column]
        public virtual bool HasDuration { get; set; }

        [Column(IsDiscriminator=true)]
        public char Type { get; set; }

        public abstract Event Clone();

        public virtual Event Persist(IDataService data)
        {
            return data.PersistEvent(this);
        }

        public void Remove(IDataService data)
        {
            data.DeleteEvent(this);
        }

        public void SetAlarm(DateTime start, DateTime end, String message, IAlarmService alarm, Action<Exception> callback)
        {
        }

        public static void DeleteExpiredAlarms(IAlarmService alarm, Action<Exception> callback)
        {
        }

        public static void RemoveAlarm(String id, DateTime date, Action<Exception> callback)
        {
        }

    }
}
