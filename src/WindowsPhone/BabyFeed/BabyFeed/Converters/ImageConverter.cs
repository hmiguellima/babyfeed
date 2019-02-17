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
using System.Windows.Data;
using System.Windows.Media.Imaging;
using System.IO.IsolatedStorage;

namespace BabyFeed.Converters
{
    public class ImageConverter:IValueConverter
    {

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string imageUri = value as string;

            if (imageUri.StartsWith("isostore:/"))
            {
                BitmapImage bitmap = new BitmapImage();
                IsolatedStorageFile store = IsolatedStorageFile.GetUserStoreForApplication();

                bitmap.SetSource(store.OpenFile(imageUri.Substring(10), System.IO.FileMode.Open));

                return bitmap;
            }
            else
                return imageUri;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
