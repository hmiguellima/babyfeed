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

namespace BabyFeed.View
{
    public class DynamicContentControl : ContentControl
    {
        private object FindResource(string resourceKey)
        {
            FrameworkElement currentElement = this;

            while (currentElement != null)
            {
                var resource = currentElement.Resources[resourceKey];
                if (resource != null)
                {
                    return resource;
                }

                currentElement = currentElement.Parent as FrameworkElement;
            }

            return Application.Current.Resources[resourceKey];
        }
        
        protected override void OnContentChanged(object oldContent, object newContent)
        {
            base.OnContentChanged(oldContent, newContent);
            //if the new content is null don't set any template
            if (newContent == null)
                return;
            //override the existing template with a template for
            //the corresponding new content
            Type t = newContent.GetType();
            
            DataTemplate template =   FindResource(t.Name.Replace("ViewModel", "Template")) as DataTemplate;
            ContentTemplate = template;
        }
    }
}
