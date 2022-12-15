using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace GUI
{
    /// <summary>
    /// Country.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Country : UserControl
    {
        public Country()
        {
            InitializeComponent();
        }

        public string CountryName
        {
            get { return (string)GetValue(CountryNameProperty); }
            set { SetValue(CountryNameProperty, value); }
        }

        public static readonly DependencyProperty CountryNameProperty =
            DependencyProperty.Register("CountryName", typeof(string), typeof(Country));

        public string Price
        {
            get { return (string)GetValue(PriceProperty); }
            set { SetValue(PriceProperty, value); }
        }

        public static readonly DependencyProperty PriceProperty =
            DependencyProperty.Register("Price", typeof(string), typeof(Country));

        public bool IsLevelUp
        {
            get { return (bool)GetValue(IsLevelUpProperty); }
            set { SetValue(IsLevelUpProperty, value); }
        }

        public static readonly DependencyProperty IsLevelUpProperty =
            DependencyProperty.Register("IsLevelUp", typeof(bool), typeof(Country));

        public ImageSource Flag
        {
            get { return (ImageSource)GetValue(FlagProperty); }
            set { SetValue(FlagProperty, value); }
        }

        public static readonly DependencyProperty FlagProperty =
            DependencyProperty.Register("Flag", typeof(ImageSource), typeof(Country));
    }
}
