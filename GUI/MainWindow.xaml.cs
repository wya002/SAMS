
using Microsoft.Win32;
using System;
using System.IO;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Navigation;
using System.Windows.Threading;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static readonly NLog.Logger Logger = NLog.LogManager.GetCurrentClassLogger();

        MyVisualHost mvh = new MyVisualHost();
        MyVisualHost mvh2 = new MyVisualHost();
        MyVisualHost mvh3 = new MyVisualHost();
        public MainWindow()
        {
            InitializeComponent();
            ImageGrid.Children.Add(mvh);
            ImageGrid.Children.Add(mvh2);
            ImageGrid.Children.Add(mvh3);

            Task.Run(async () => {
                for (int i = 0; ; i++)
                {
                    await Task.Delay(TimeSpan.FromSeconds(3)).ConfigureAwait(false);
                    Logger.Debug("Log {0}", i);
                }
            });
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

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var config = new NLog.Config.LoggingConfiguration();

            // Targets where to log to: custom target
            var wpfLogger = new NLogCustomTarget();
            wpfLogger.LogEventListener += WriteLogToTextBox;

            // Rules for mapping loggers to targets
            config.AddRule(NLog.LogLevel.Debug, NLog.LogLevel.Fatal, wpfLogger);

            // Apply config           
            NLog.LogManager.Configuration = config;
        }

        private void Menubutton_LostMouseCapture_2(object sender, MouseEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.InitialDirectory = @"C:\Users\User\Scenario";
            dlg.FileName = "UnnamedScenario.xml"; // Default file name
            dlg.DefaultExt = ".xml"; // Default file extension
            dlg.Filter = "Scenario File (.xml)|*.xml"; // Filter files by extension

            if(dlg.ShowDialog() == true)
            {
                string str = dlg.FileName;
                if (!File.Exists(str))
                {
                    FileStream stream = File.Create(str);
                    stream.Close();
                }
            }
        }
        private void mapImage_MouseDown(object sender, MouseButtonEventArgs e)
        {

        }

        private void Button_LostMouseCapture(object sender, MouseEventArgs e)
        {

        }

        private void mapImage_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Point ClickPos = e.GetPosition((IInputElement)sender);

            int ClickX = (int)ClickPos.X;
            int ClickY = (int)ClickPos.Y;
            ATSX1.Text = ClickX.ToString();
            ATSY1.Text = ClickY.ToString();
            mvh.Drawrect(new System.Windows.Point(ClickX, ClickY));
        }

        private void mapImage_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            Point ClickPos = e.GetPosition((IInputElement)sender);

            int ClickX = (int)ClickPos.X;
            int ClickY = (int)ClickPos.Y;
            ATSX2.Text = ClickX.ToString();
            ATSY2.Text = ClickY.ToString();
            mvh.Drawrect2(new System.Windows.Point(ClickX, ClickY));
        }

        private void mapImage_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            Point ClickPos = e.GetPosition((IInputElement)sender);

            int ClickX = (int)ClickPos.X;
            int ClickY = (int)ClickPos.Y;
            MSSX.Text = ClickX.ToString();
            MSSY.Text = ClickY.ToString();
            mvh.Drawrect3(new System.Windows.Point(ClickX, ClickY));
        }

        private void WriteLogToTextBox(string log)
        {
            TbLog.Dispatcher.BeginInvoke(new Action(() => {
                TbLog.AppendText(string.Format("\n{0}", log));
            }));
            TbLog.ScrollToEnd();
        }
    }
}