using System;
using System.Windows.Data;
using BabyFeed.ViewModel;

namespace BabyFeed.Converters
{
    public class StepTitleConverter:IValueConverter
    {

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            WizardStep vm = value as WizardStep;
            if (vm != null)
            {
                string title = vm.Title;
                if (vm.Wizard != null)
                {
                    int idx = vm.Wizard.Steps.IndexOf(vm);
                    title += " ( " + (idx+1) + " of " + vm.Wizard.Steps.Count + " )";
                }
                return title;
            }
            return null;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
