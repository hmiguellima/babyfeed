using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BabyFeed.Provider
{
    public interface INavigationService
    {
        void NavigateTo(Uri pageUri);
        void GoBack();
    }
}
