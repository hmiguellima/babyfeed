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

namespace BabyFeed.Domain
{
    public class BabyEventGroup : IEnumerable<Event>
    {
        public string Title
        {
            get;
            set;
        }

        public IList<Event> Items
        {
            get;
            set;
        }

        public override int GetHashCode()
        {
            return Title.GetHashCode();
        }

        public override bool Equals(object obj)
        {
            BabyEventGroup that = obj as BabyEventGroup;

            return (that != null) && (this.Title.Equals(that.Title));
        }

        public BabyEventGroup(string name, IEnumerable<Event> items)
        {
            Title = name;
            Items = new List<Event>(items);
        }

        public IEnumerator<Event> GetEnumerator()
        {
            return Items.GetEnumerator();
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return Items.GetEnumerator();
        }
    }
}
