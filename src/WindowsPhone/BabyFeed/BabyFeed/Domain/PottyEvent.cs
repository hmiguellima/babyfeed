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
    public class PottyEvent : Event
    {

        public override string Icon
        {
            get 
            {
                return "/icons/nappy" + (Checked ? "_checked.png" : ".png");
            }
        }

        public override string ShortDesc
        {
            get 
            { 
                return "At: "+StartDate.ToString("hh:mm");
            }
        }

        public override string AlarmDesc
        {
            get { throw new NotImplementedException(); }
        }

        public override bool Recurrentable
        {
            get { throw new NotImplementedException(); }
        }

        public override Event Clone()
        {
            throw new NotImplementedException();
        }
    }
}
