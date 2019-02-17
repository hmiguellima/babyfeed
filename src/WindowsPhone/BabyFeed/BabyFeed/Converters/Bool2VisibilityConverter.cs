using System;
using System.Windows.Data;
using System.Windows;

namespace BabyFeed.Converters
{
    public class Bool2VisibilityConverter:IValueConverter
    {
        public Visibility FalseVisibility { get; set; }
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((bool)value)
                return Visibility.Visible;
            return FalseVisibility;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
