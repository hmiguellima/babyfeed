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
    public class RFeedingEvent : FeedingEvent
    {
        public override string Icon
        {
            get
            {
                return "/icons/breastfeeding-right" + (Checked ? "_checked.png" : ".png");
            }
        }

    }
}
