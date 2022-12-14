
using Microsoft.Win32;
using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Navigation;
using System.Windows.Threading;
using OpenCvSharp;
using Point = System.Windows.Point;
using System.Drawing;
using System.Windows.Media.Imaging;
using System.Reflection;
using System.Windows.Controls;
using System.ComponentModel;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : System.Windows.Window
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

            //로그 찍는 메서드
            /*Task.Run(async () => {
                for (int i = 0; ; i++)
                {
                    await Task.Delay(TimeSpan.FromSeconds(1)).ConfigureAwait(false);
                    Logger.Debug("Log {0}", i);
                }
            });*/
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
            System.Windows.Window.GetWindow(this).Close();
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
            //로그 찍는 메서드
            /*var config = new NLog.Config.LoggingConfiguration();

            // Targets where to log to: custom target
            var wpfLogger = new NLogCustomTarget();
            wpfLogger.LogEventListener += WriteLogToTextBox;

            // Rules for mapping loggers to targets
            config.AddRule(NLog.LogLevel.Debug, NLog.LogLevel.Fatal, wpfLogger);

            // Apply config           
            NLog.LogManager.Configuration = config;*/
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
            System.Windows.Point ClickPos = e.GetPosition((IInputElement)sender);

            int ClickX = (int)ClickPos.X;
            int ClickY = (int)ClickPos.Y;
            ATSX1.Text = ClickX.ToString();
            ATSY1.Text = ClickY.ToString();
            mvh.isExist();
            mvh.Drawrect(new System.Windows.Point(ClickX, ClickY));
        }

        private void mapImage_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            Point ClickPos = e.GetPosition((IInputElement)sender);

            int ClickX = (int)ClickPos.X;
            int ClickY = (int)ClickPos.Y;
            ATSX2.Text = ClickX.ToString();
            ATSY2.Text = ClickY.ToString();
            mvh2.isExist();
            mvh2.Drawrect2(new System.Windows.Point(ClickX, ClickY));
        }

        private void mapImage_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            Point ClickPos = e.GetPosition((IInputElement)sender);

            int ClickX = (int)ClickPos.X;
            int ClickY = (int)ClickPos.Y;
            MSSX.Text = ClickX.ToString();
            MSSY.Text = ClickY.ToString();
            mvh3.isExist();
            mvh3.Drawrect3(new System.Windows.Point(ClickX, ClickY));
        }

        private void WriteLogToTextBox(string log)
        {
            //로그 찍는 메서드
            /*TbLog.Dispatcher.BeginInvoke(new Action(() => {
                TbLog.ScrollToEnd();
                TbLog.AppendText(string.Format("\n{0}", log));
            }));*/
        }

        private void mapImage_Initialized(object sender, EventArgs e)
        {
          
        }

        private void Launch_button_LostMouseCapture(object sender, MouseEventArgs e)
        {

        }

        public static Bitmap MatToBitmap(Mat image)
        {
            return OpenCvSharp.Extensions.BitmapConverter.ToBitmap(image);
        }

        BitmapImage BitmapToImageSource(Bitmap bitmap)
        {
            using (MemoryStream memory = new MemoryStream())
            {
                bitmap.Save(memory, System.Drawing.Imaging.ImageFormat.Bmp);
                memory.Position = 0;
                BitmapImage bitmapimage = new BitmapImage();
                bitmapimage.BeginInit();
                bitmapimage.StreamSource = memory;
                bitmapimage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapimage.EndInit();

                return bitmapimage;
            }
        }

        private void ScenarioStart_LostMouseCapture(object sender, MouseEventArgs e)
        {
            startScenario();
        }
        private Tuple<double, double> linear_equ(double x1, double y1, double x2, double y2, double X)
        {
            double d_x = x2 - x1;
            double d_y = y2 - y1;

            double a = (d_y / d_x);

            double Y = a * (X - x1) + y1;

            return Tuple.Create(X,Y);
        }

        private double distance(double X, double Y, double x3, double y3)
        {

            double d_x = Math.Pow(x3 - X, 2);
            double d_y = Math.Pow(y3 - Y, 2);

            double dis = Math.Sqrt(d_x + d_y);

            return dis;
        }

        private Tuple<double, double> get_velocity(double x1, double y1, double x2, double y2)
        {
                
            double vel = 250; // 대공 유도탄 미사일의 속도

            double v_x;
            double v_y;

            v_x = vel * (x2 - x1) / Math.Sqrt(Math.Pow(x2 - x1, 2) + Math.Pow(y2 - y1, 2));
            v_y = vel * (y2 - y1) / Math.Sqrt(Math.Pow(x2 - x1, 2) + Math.Pow(y2 - y1, 2));

            return Tuple.Create(v_x, v_y);
        }

        private Tuple<double, double> get_MSS_Pos(double MSS_x, double MSS_y, double v_x, double v_y)
        {

            double time = 0.01;
            double X = MSS_x + time * v_x;
            double Y = MSS_y + time * v_y;

            return Tuple.Create<double, double>(X, Y);
        }

        private void Menubutton_LostMouseCapture_3(object sender, MouseEventArgs e)
        {
            try
            {
                //System.Windows.Forms.Application.Restart();
                mapImage.Source = new BitmapImage(new Uri("C:/Users/User/source/repos/wya002/SAMS/GUI/map6.png"));
                Launch_button.IsEnabled = false;
                mvh.Clear();
                mvh2.Clear();
                mvh3.Clear();
                ATS_current_x.Text = "";
                ATS_current_y.Text = "";
                MSS_current_x.Text = "";
                MSS_current_y.Text = "";
                ATSX1.Text = "";
                ATSY1.Text = "";
                ATSX2.Text = "";
                ATSY2.Text = "";
                MSSX.Text = "";
                MSSY.Text = "";
                target_distance.Text = "";
                //System.Windows.Application.Current.Shutdown();
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }

        private void startScenario()
        {
            Mat mat1 = new("C:/Users/User/source/repos/wya002/SAMS/GUI/map6.png", ImreadModes.Color);
            Mat mat2 = new("C:/Users/User/source/repos/wya002/SAMS/GUI/map6.png", ImreadModes.Color);

            double ATS_init_x = Convert.ToInt64(ATSX1.Text); // 시나리오 초기 발사 x 위치
            double ATS_init_y = Convert.ToInt64(ATSY1.Text); // 시나리오 초기 발사 y 위치

            double ATS_target_x = Convert.ToInt64(ATSX2.Text); // 시나리오 목표 발사 x 위치
            double ATS_target_y = Convert.ToInt64(ATSY2.Text); // 시나리오 목표 발사 y 위치

            double ATS_cur_x = Convert.ToInt64(ATSX1.Text); // ATS 현재 x 위치
            double ATS_cur_y = Convert.ToInt64(ATSY1.Text); // ATS 현재 y 위치

            double MSS_init_x = Convert.ToInt64(MSSX.Text);
            double MSS_init_y = Convert.ToInt64(MSSY.Text);

            double MSS_cur_x = MSS_init_x;
            double MSS_cur_y = MSS_init_y;

            int RaderRange = 200;

            double diss = 2; // ATS와 MSS 사이 pixel

            double v_x = 0; // MSS x 방향 속도
            double v_y; // MSS y 방향 속도

            Cv2.Line(mat1, new OpenCvSharp.Point(ATS_init_x, ATS_init_y), new OpenCvSharp.Point(ATS_target_x, ATS_target_y), new OpenCvSharp.Scalar(0, 255, 0), 3);
            Cv2.Circle(mat1, Convert.ToInt32(MSS_init_x), Convert.ToInt32(MSS_init_y), RaderRange, Scalar.Red, 3);

            while (Cv2.WaitKey(20) != 'q')
            {
                Tuple<double, double> result = linear_equ(ATS_init_x, ATS_init_y, ATS_target_x, ATS_target_y, ATS_cur_x);

                ATS_cur_x = result.Item1;
                ATS_cur_y = result.Item2;
                ATS_current_x.Text = Convert.ToInt32(ATS_cur_x).ToString();
                ATS_current_y.Text = Convert.ToInt32(ATS_cur_y).ToString();
                if (ATSX1.Text == "")
                {
                    ATS_current_x.Text = "";
                    ATS_current_y.Text = "";
                    break;
                }
                if (ATS_cur_x >= ATS_target_x) break;

                Cv2.Line(mat1, new OpenCvSharp.Point(ATS_cur_x, ATS_cur_y), new OpenCvSharp.Point(ATS_cur_x, ATS_cur_y), new OpenCvSharp.Scalar(0, 0, 0), 5);
                double dis = distance(MSS_init_x, MSS_init_y, ATS_cur_x, ATS_cur_y);
                if (dis <= RaderRange)
                {
                    Launch_button.IsEnabled = true;
                    Cv2.Line(mat1, new OpenCvSharp.Point(MSS_cur_x, MSS_cur_y), new OpenCvSharp.Point(MSS_cur_x, MSS_cur_y), Scalar.White, 5);

                    Tuple<double, double> result2 = get_velocity(MSS_cur_x, MSS_cur_y, ATS_cur_x, ATS_cur_y);
                    v_x = result2.Item1;
                    v_y = result2.Item2;

                    Tuple<double, double> result3 = get_MSS_Pos(MSS_cur_x, MSS_cur_y, v_x, v_y);
                    MSS_cur_x = result3.Item1;
                    MSS_cur_y = result3.Item2;
                    MSS_current_x.Text = Convert.ToInt32(MSS_cur_x).ToString();
                    MSS_current_y.Text = Convert.ToInt32(MSS_cur_y).ToString();

                    double dis2 = distance(MSS_cur_x, MSS_cur_y, ATS_cur_x, ATS_cur_y);
                    target_distance.Text = Convert.ToInt32(dis2).ToString();

                    double dis2_x = MSS_cur_x - ATS_cur_x;
                    double dis2_y = MSS_cur_y - ATS_cur_y;

                    if (dis2 < 1) break;
                    else if (-diss < dis2_x && dis2_x < diss && -diss < dis2_y && dis2_y < diss) break;
                    if (ATSX1.Text == "")
                    {
                        ATS_current_x.Text = "";
                        ATS_current_y.Text = "";
                        break;
                    }
                }

                Cv2.Resize(mat1, mat2, new OpenCvSharp.Size(1000, 800));
                Bitmap bitimg = MatToBitmap(mat2);
                mapImage.Source = BitmapToImageSource(bitimg);

                ATS_cur_x += 1;
            }
        }
    }
}