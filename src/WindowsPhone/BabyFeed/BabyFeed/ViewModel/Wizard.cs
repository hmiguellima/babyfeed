using System;
using System.Linq;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace BabyFeed.ViewModel
{
    public class Wizard:INotifyPropertyChanged
    {
        #region fields
        private string title;
        private ObservableCollection<WizardStep> steps;
        private WizardStep currentStep;
        private bool showCancel;
        #endregion

        public Wizard()
        {
            steps = new ObservableCollection<WizardStep>();
            steps.CollectionChanged += (o, e) => {
                OnStepCollectionChanged();
            };
        }

        #region inpc implementation
        public event PropertyChangedEventHandler PropertyChanged;
        protected void NotifyPropertyChanged(string name)
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
        public ObservableCollection<WizardStep> Steps
        {
            get { return steps; }
        }
        public WizardStep CurrentStep
        {
            get { return currentStep; }
            set
            {
                if (currentStep == value)
                    return;
                currentStep = value;
                NotifyPropertyChanged("CurrentStep");
                Invalidate();
            }
        }
        public bool ShowCancel
        {
            get { return showCancel; }
            set
            {
                if (showCancel == value)
                    return;
                showCancel = value;
                NotifyPropertyChanged("ShowCancel");
            }
        }
        #endregion

        #region validation properties
        public bool CanNext
        {
            get
            {
                //can always move forward if valid
                int idx = steps.IndexOf(currentStep);
                return idx < (steps.Count - 1) && CurrentStep.IsValid();
            }
        }
        public bool CanPrevious
        {
            get
            {
                WizardStep prev = GetPreviousAvailableStep();
                return prev != null;
            }
        }
        public bool CanFinish
        {
            get
            {
                //can only finish if the user is on the last step
                //derived classes can say otherwise
                int idx = steps.IndexOf(currentStep);
                if (steps.Count == 0 || currentStep == null || !currentStep.IsValid())
                    return false;
                if (idx < steps.Count - 1 && currentStep.AllowFinish)
                    return true;
                return idx == steps.Count - 1;
            }
        }
        public bool CanCancel
        {
            get
            {
                //can cancel only if show cancel is true and there are steps
                return steps.Count > 0 && ShowCancel;
            }
        }
        #endregion

        #region events
        public event EventHandler WizardCanceled;
        public event EventHandler WizardFinished;
        #endregion

        #region helper functions
        protected void OnWizardCanceled()
        {
            if (WizardCanceled != null)
                WizardCanceled(this, EventArgs.Empty);
        }
        protected void OnWizardFinished()
        {
            if (WizardFinished != null)
                WizardFinished(this, EventArgs.Empty);
        }
        private WizardStep GetPreviousAvailableStep()
        {
            int idx = steps.IndexOf(currentStep);
            for (int i = idx - 1; i >= 0; i--)
            {
                if (steps.ElementAt(i).AllowReturn)
                    return steps.ElementAt(i);
            }
            return null;
        }
        private void OnStepCollectionChanged()
        {
            //set the current step only when the first step is added or when
            //the current step is removed from the wizard
            if (steps.Count == 1 || steps.IndexOf(currentStep) == -1)
                CurrentStep = steps.ElementAt(0);
        }
        #endregion

        #region virtual methods 
        public virtual void Next()
        {
            if (CanNext)
            {
                //move to the next step
                int idx = steps.IndexOf(currentStep);
                CurrentStep = steps.ElementAt(idx + 1);
            }
        }
        
        public virtual void Previous()
        {
            //take into account the allowReturn value
            WizardStep prev = GetPreviousAvailableStep();
            if (prev != null)
            {
                CurrentStep = prev;
            }
        }
        
        public virtual void Finish()
        {
            if (CanFinish)
                OnWizardFinished();
        }
        
        public virtual void Cancel()
        {
            if (CanCancel)
                OnWizardCanceled();
        }
        
        #endregion

        #region public methods
        public void AddStep(WizardStep step)
        {
            if (step.Wizard != null && step.Wizard != this)
                step.Wizard.Steps.Remove(step);
            if (step.Wizard == this)
                return;
            step.Wizard = this;
            Steps.Add(step);
        }
        public void AddStep(string title, object content)
        {
            AddStep(title, content, false, true);
        }
        public void AddStep(string title, object content, bool allowFinish, bool allowReturn)
        {
            WizardStep vm = new WizardStep();
            vm.Title = title;
            vm.Content = content;
            vm.Wizard = this;
            vm.AllowFinish = allowFinish;
            vm.AllowReturn = allowReturn;
            Steps.Add(vm);
        }
        public virtual void Invalidate() 
        {
            NotifyPropertyChanged("CanNext");
            NotifyPropertyChanged("CanPrevious");
            NotifyPropertyChanged("CanCancel");
            NotifyPropertyChanged("CanFinish");
        } 
        #endregion
    }
}
