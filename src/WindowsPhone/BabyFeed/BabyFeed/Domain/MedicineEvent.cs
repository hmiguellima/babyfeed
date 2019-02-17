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
    public class MedicineEvent : Event
    {
        public MedicineEvent()
        {
            string notes="|";
            base.Notes=notes;
            Type=Event.TYPE_MEDICINE;
        }

        public override string Icon
        {
            get
            {
                return "/icons/Pills" + (Checked ? "_checked.png" : ".png");
            }
        }


        public string MedicineName
        {
            get
            {
                return base.Notes.Split(new char[] {'|'})[0];
            }

            set
            {
                string notes=value+"|"+Notes;
                base.Notes=notes;
            }
        }

        public override string Notes
        {
            get
            {
                return base.Notes.Split(new char[]{'|'})[1];
            }

            set
            {
                string newNotes=MedicineName+"|"+value;
                base.Notes=newNotes;
            }
        }
        
        public override string ShortDesc
        {
            get 
            { 
                string eventData;

                eventData=MedicineName+" at: "+StartDate.ToString("hh:mm");

                return eventData;
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
