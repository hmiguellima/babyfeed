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
    public class EmptyEvent : Event
    {
        public override string Icon
        {
            get 
            {
                return "";
            }
        }

        public override string ShortDesc
        {
            get
            {
                return "<No events>";
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
