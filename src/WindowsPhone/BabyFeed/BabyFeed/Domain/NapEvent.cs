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
    public class NapEvent : Event
    {

        public override string Icon
        {
            get 
            {
                return "/icons/baby_sleep" + (Checked ? "_checked.png" : ".png");
            }
        }

        public override string ShortDesc
        {
            get 
            {
                string eventData;
                int min;
                DateTime endTime;

                min = Duration;
                endTime = StartDate.AddSeconds(min * 60);
                eventData = "from " + StartDate.ToString("hh:mm") + " to " + endTime.ToString("hh:mm");

                return eventData;
            }
        }

        public override string AlarmDesc
        {
            get 
            { 
                throw new NotImplementedException(); 
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
