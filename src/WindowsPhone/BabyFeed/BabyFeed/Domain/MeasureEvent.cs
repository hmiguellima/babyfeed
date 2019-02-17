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
    public class MeasureEvent : Event
    {
        public override String ShortDesc
        {
            get
            {
                return String.Format(AppResx.measures, (float)Weight / 100, (float)Height / 100, (float)Cephalic / 100);
            }
        }

        public override String AlarmDesc
        {
            get
            {
                return "";
            }
        }

        public override string Icon
        {
            get
            {
                return "/icons/weight" + (Checked ? "_checked.png" : ".png");
            }
        }

        public override Event Clone()
        {
            MeasureEvent evt=new MeasureEvent();

            evt.Weight=Weight;
            evt.Height=Height;
            evt.Cephalic=Cephalic;

            return evt;
        }

        public override bool Recurrentable
        {
            get
            {
                return false;
            }
        }
    }
}
