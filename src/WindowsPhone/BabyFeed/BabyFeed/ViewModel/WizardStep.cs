using System;
using System.ComponentModel;
using System.Reflection;
using System.Diagnostics;

namespace BabyFeed.ViewModel
{
    public sealed class WizardStep:IValidableContent, INotifyPropertyChanged
    {
        #region fields
        private string title;
        private bool allowReturn;
        private Wizard wizard;
        private object content;
        private bool allowFinish;
        #endregion

        public WizardStep()
        {
            AllowReturn = true;
        }

        #region inpc implementation
        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged(string name)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(name));
        }
        #endregion

        #region properties
        public string Title
        {
            get { return title; }
            set 
            {
                if (title == value)
                    return;
                title = value;
                NotifyPropertyChanged("Title");
            }
        }       

        public bool AllowReturn
        {
            get { return allowReturn; }
            set 
            {
                if (allowReturn == value)
                    return;
                allowReturn = value;
                NotifyPropertyChanged("AllowReturn");
            }
        }
        public bool AllowFinish
        {
            get { return allowFinish; }
            set
            {
                if (allowFinish == value)
                    return;
                allowFinish = value;
                NotifyPropertyChanged("AllowFinish");
            }
        }    

        public Wizard Wizard
        {
            get { return wizard; }
            set 
            {
                if (wizard == value)
                    return;
                wizard = value;
                NotifyPropertyChanged("Wizard");
            }
        }

        public object Content
        {
            get { return content; }
            set
            {
                if (content == value)
                    return;
                //unsubscribe the old content
                unsubscribe(content);
                //set the new content
                content = value;
                //subscribe the new content
                subscribe(content);
                NotifyPropertyChanged("Content");
                //also invalidate the commands
                if (wizard != null)
                    wizard.Invalidate();
            }
        }
        #endregion

        public bool IsValid()
        {
            IValidableContent v = content as IValidableContent;
            if (v != null)
                return v.IsValid();
            return true;
        }

        #region private helpers
        private void ContentChanged(object sender, PropertyChangedEventArgs e)
        {
            //when any property changes invalidate the wizard commands
            if (wizard != null)
                Wizard.Invalidate();
        }
        private void subscribe(object obj)
        {
            INotifyPropertyChanged c = obj as INotifyPropertyChanged;
            if (c != null)
                c.PropertyChanged += ContentChanged;
            else
                return;
            Debug.WriteLine("subscribed " + obj);
            Type type = obj.GetType();
            //get all the public properties
            PropertyInfo[] pis = type.GetProperties();
            //iterate over them and call subscribe()
            for (int i = 0; i < pis.Length; i++)
            {
                object val = pis[i].GetValue(obj, null);
                //call subscribe() recursively even if it does not 
                //implement inpc. this will be checked anyway the next time
                //subscribe() is called
                subscribe(val);
            }
        }
        private void unsubscribe(object obj)
        {
            INotifyPropertyChanged c = obj as INotifyPropertyChanged;
            if (c != null)
                c.PropertyChanged -= ContentChanged;
            else
                return;
            Debug.WriteLine("unsubscribed "+ obj);
            Type type = obj.GetType();
            //get all the public properties
            PropertyInfo[] pis = type.GetProperties();
            //iterate over them and call unsubscribe()
            for (int i = 0; i < pis.Length; i++)
            {
                object val = pis[i].GetValue(obj, null);
                //call unsubscribe() recursively even if it does not 
                //implement inpc. this will be checked anyway the next time
                //unsubscribe() is called
                unsubscribe(val);
            }
        }
        #endregion

        #region destructor
        ~WizardStep()
        {
            unsubscribe(content);
        }
        #endregion
    }
}
