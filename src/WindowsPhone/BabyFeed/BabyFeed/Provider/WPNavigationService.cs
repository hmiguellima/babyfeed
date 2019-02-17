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
using Microsoft.Phone.Controls;

namespace BabyFeed.Provider
{
    public class WPNavigationService : INavigationService
    {
        private PhoneApplicationFrame _mainFrame;

        public void NavigateTo(Uri pageUri)
        {
            if (EnsureMainFrame())
                _mainFrame.Navigate(pageUri);
        }

        public void GoBack()
        {
            if (EnsureMainFrame())
                _mainFrame.GoBack();
        }

        private bool EnsureMainFrame()
        {
            if (_mainFrame != null)
                return true;

            _mainFrame = Application.Current.RootVisual as PhoneApplicationFrame;

            return (_mainFrame != null);
        }
    }
}
