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
    public class NoBaby : Baby
    {
        public override String Name
        {
            get
            {
                return BabyFeed.AppResx.newbaby;
            }
        }

        public override String Photo
        {
            get
            {
                return "/icons/baby_add.png";
            }
        }

        public override int Id
        {
            get
            {
                return -1;
            }
        }

        public override Baby.Genders Gender
        {
            get
            {
                return Baby.Genders.NewBaby;
            }
        }

        public override bool Selected
        {
            get
            {
                return false;
            }
        }

        public override String Age
        {
            get
            {
                return "";
            }
        }

    }
}
