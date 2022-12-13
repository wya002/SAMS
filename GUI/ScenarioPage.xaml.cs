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
    /// ScenarioPage.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class ScenarioPage : Page
    {
        public ScenarioPage()
        {
            InitializeComponent();
        }
        

        //종료 버튼 클릭
        private void Menubutton_LostMouseCapture(object sender, MouseEventArgs e)
        {
            Window.GetWindow(this).Close();
        }
        //홈 버튼 클릭
        private void Menubutton_LostMouseCapture_1(object sender, MouseEventArgs e)
        {
            MainWindow main = new MainWindow();
            main.Show();
            Window.GetWindow(this).Close();
        }

        private void Menubutton_Loaded(object sender, RoutedEventArgs e)
        {

        }
    }
}
