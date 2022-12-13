
using System;
using System.Timers;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Navigation;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Border_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if(e.ChangedButton == MouseButton.Left)
            {
                this.DragMove();
            }
        }

        private void Menubutton_MouseEnter(object sender, MouseEventArgs e)
        {
            this.Close();
        }

        private void Menubutton_Loaded(object sender, RoutedEventArgs e)
        {

        }
        //종료 이벤트 버튼 클릭
        private void Menubutton_Clicked(object sender, MouseButtonEventArgs e)
        {
            
        }
        //시나리오 페이지 이동
        private void Menubutton_LostMouseCapture(object sender, MouseEventArgs e)
        {
            Window.GetWindow(this).Close();
        }

        private void PackIconMaterial_Initialized(object sender, EventArgs e)
        {

        }

        private void Menubutton_LostMouseCapture_1(object sender, MouseEventArgs e)
        {
            ScenarioLoad load = new ScenarioLoad();
            load.ShowDialog();
        }
    }
}