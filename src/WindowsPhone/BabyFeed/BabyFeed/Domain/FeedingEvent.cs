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

namespace BabyFeed.Domain
{
    public abstract class FeedingEvent : Event
    {
        public override string ShortDesc
        {
            get 
            { 
                string eventData;
                int min;
                DateTime endTime;

                if (StartDate > DateTime.Now)
                    eventData="At: "+StartDate.ToString("hh:mm");
                else
                {
                    min=Duration;
                    endTime=StartDate.AddSeconds(min*60);
                    eventData="End: "+endTime.ToString("hh:mm")+", Min.: "+min.ToString();
                }

                return eventData;
            }
        }

        public override string AlarmDesc
        {
            get 
            {
                return "";
            }
        }

        public override bool Recurrentable
        {
            get 
            {
                return false;
            }
        }

        public override Event Clone()
        {
            throw new NotImplementedException();
        }
    }
}
