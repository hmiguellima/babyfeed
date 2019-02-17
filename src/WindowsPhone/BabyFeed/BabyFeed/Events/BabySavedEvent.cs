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
using BabyFeed.Domain;

namespace BabyFeed.Events
{
    public class BabySavedEvent
    {
        public Baby Baby { get; set; }

        public BabySavedEvent(Baby baby)
        {
            Baby = baby;
        }
    }
}
