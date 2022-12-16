
using System;
using System.Drawing;
using System.IO;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using Microsoft.Win32;
using OpenCvSharp;
using Point = System.Windows.Point;
using TCCLibrary;
using System.Threading;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>s
    public partial class MainWindow : System.Windows.Window
    {
        TCCLibrary.WrapperClass wc = new WrapperClass();

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
            Thread myThread = new Thread(Func);
            myThread.Start();
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
        }

        private string xmlParse()
        {
            string parse =
                "<?xml version=\"1.0\" ?>\n" +
                "<DB>\n" + "   <Synario>\n" + "        <SynarioStart Position=\"Value\"" + " Start=\"" + ATSX1.Text + "\" End=\"" + ATSY1.Text + "\" />\n" +
                "        <SynarioDestination Position=\"Value\"" + " Start=\"" + ATSX2.Text + "\" End=\"" + ATSY2.Text + "\" />\n" +
                "        <SynarioMSS Position=\"Value\"" + " Start=\"" + MSSX.Text + "\" End=\"" + MSSY.Text + "\" />\n" +
                "   </Synario>\n" + "</DB>\n";
            return parse;
        }

        private void Menubutton_LostMouseCapture_2(object sender, MouseEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.InitialDirectory = @"C:\Users\User\Scenario";
            dlg.FileName = "UnnamedScenario.xml"; // Default file name
            dlg.DefaultExt = ".xml"; // Default file extension
            dlg.Filter = "Scenario File (.xml)|*.xml"; // Filter files by extension

            if (dlg.ShowDialog() == true)
            {
                string str = dlg.FileName;
                System.IO.File.WriteAllText(str, xmlParse());
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
            wc.start();
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
                
            double vel = 350; // 대공 유도탄 미사일의 속도

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
                TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 시나리오 중지 \n";
                TbLog.Text += "--------------------------------------------  \n";
                //System.Windows.Forms.Application.Restart();
                mapImage.Source = new BitmapImage(new Uri("C:/Users/User/source/repos/wya002/SAMS/GUI/map6.png"));
                ScenarioStart.IsActive = false;
                ScenarioStart.IsEnabled = true;
                pause.IsActive = false;
                pause.IsEnabled = true;
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
                command = "";
                command2 = "";
                //System.Windows.Application.Current.Shutdown();
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }
        
        private void startScenario()
        {
            //시나리오가 입력되어 있지 않으면, 시작 버튼을 눌러도 반응 없음
            if (ATSX1.Text != "" && ATSX2.Text != "" && ATSY1.Text != "" && ATSY2.Text != "" && MSSX.Text != "" && MSSY.Text != "")
            {
                ScenarioStart.IsActive = true;
                Mat mat1 = new("C:/Users/User/source/repos/wya002/SAMS/GUI/map6.png", ImreadModes.Color);
                Mat mat2 = new("C:/Users/User/source/repos/wya002/SAMS/GUI/map6.png", ImreadModes.Color);

                double ATS_init_x = Convert.ToInt64(ATSX1.Text); // 시나리오 ATS 초기 발사 x 위치
                double ATS_init_y = Convert.ToInt64(ATSY1.Text); // 시나리오 ATS 초기 발사 y 위치

                double ATS_target_x = Convert.ToInt64(ATSX2.Text); // 시나리오 ATS 목표 발사 x 위치
                double ATS_target_y = Convert.ToInt64(ATSY2.Text); // 시나리오 ATS 목표 발사 y 위치

                double ATS_cur_x = Convert.ToInt64(ATSX1.Text); // ATS 현재 x 위치
                double ATS_cur_y = Convert.ToInt64(ATSY1.Text); // ATS 현재 y 위치

                double MSS_init_x = Convert.ToInt64(MSSX.Text); // 시나리오 MSS 초기 발사 x 위치
                double MSS_init_y = Convert.ToInt64(MSSY.Text); // 시나리오 MSS 초기 발사 y 위치

                double MSS_cur_x = MSS_init_x; // MSS 현재 x 위치
                double MSS_cur_y = MSS_init_y; // MSS 현재 y 위치

                int RaderRange = 200; // 레이더 탐지 거리

                double diss = 2; // ATS와 MSS 사이 pixel

                double v_x = 0; // MSS x 방향 속도
                double v_y = 0; // MSS y 방향 속도

                TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 시나리오 시작 \n";

                Cv2.Line(mat1, new OpenCvSharp.Point(ATS_init_x, ATS_init_y), new OpenCvSharp.Point(ATS_target_x, ATS_target_y), new OpenCvSharp.Scalar(0, 255, 0), 3); // ATS 경로 생성
                Cv2.Circle(mat1, Convert.ToInt32(MSS_init_x), Convert.ToInt32(MSS_init_y), RaderRange, Scalar.Red, 3); // 레이더 탐지 영역 생성

                while (true)
                {
                    if (ATS_init_x != ATS_target_x)
                    {
                        Tuple<double, double> result = linear_equ(ATS_init_x, ATS_init_y, ATS_target_x, ATS_target_y, ATS_cur_x); // ATS 경로에 대한 직선의 방정식 계산
                        ATS_cur_x = result.Item1;
                        ATS_cur_y = result.Item2; // 직선의 방정식에 ATS 현재 x 위치 값에 따른 계산된 y 위치 값
                    }

                    ATS_current_x.Text = Convert.ToInt32(ATS_cur_x).ToString();
                    ATS_current_y.Text = Convert.ToInt32(ATS_cur_y).ToString();

                    if (ATSX1.Text == "")
                    {
                        ATS_current_x.Text = "";
                        ATS_current_y.Text = "";
                        break;
                    }
                    if (ATS_cur_x == ATS_target_x)
                    {
                        TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 시나리오 종료 \n";
                        TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 공중위협 요격 실패 \n";
                        wc.done();
                        //TbLog.Text += "--------------------------------------------  \n";
                        break;
                    }

                    Cv2.Line(mat1, new OpenCvSharp.Point(ATS_cur_x, ATS_cur_y), new OpenCvSharp.Point(ATS_cur_x, ATS_cur_y), new OpenCvSharp.Scalar(0, 0, 0), 5); // ATS의 현재 위치 표시
                    double dis = distance(MSS_init_x, MSS_init_y, ATS_cur_x, ATS_cur_y); // ATS와 ATTS 탐지기 사이의 거리 계산
                    if (dis <= RaderRange) // ATS가 레이더 탐지 거리 내에 들어왔을 경우, True
                    {
                        Launch_button.IsEnabled = true; // launch 버튼 활성화
                    }

                    if (command2 == "launch" || command == "restart")
                    {
                        Launch_button.IsEnabled = true;

                        if (command2 == "launch") // 발사 버튼이 누르는 경우, True
                        {
                            Cv2.Line(mat1, new OpenCvSharp.Point(MSS_cur_x, MSS_cur_y), new OpenCvSharp.Point(MSS_cur_x, MSS_cur_y), Scalar.White, 5); // MSS의 이전 위치 표시

                            Tuple<double, double> result2 = get_velocity(MSS_cur_x, MSS_cur_y, ATS_cur_x, ATS_cur_y); // MSS의 속도 계산
                            v_x = result2.Item1; // MSS의 x 방향 속도
                            v_y = result2.Item2; // MSS의 y 방향 속도

                            Tuple<double, double> result3 = get_MSS_Pos(MSS_cur_x, MSS_cur_y, v_x, v_y); // MMS 속도에 따른 현재 위치 계산
                            MSS_cur_x = result3.Item1; // MSS의 현재 x 위치
                            MSS_cur_y = result3.Item2; // MSS의 현재 y 위치

                            MSS_current_x.Text = Convert.ToInt32(MSS_cur_x).ToString();
                            MSS_current_y.Text = Convert.ToInt32(MSS_cur_y).ToString();


                            double dis2 = distance(MSS_cur_x, MSS_cur_y, ATS_cur_x, ATS_cur_y); // 현재 ATS 위치와 현재 MSS 위치 사이의 직선 거리
                            target_distance.Text = Convert.ToInt32(dis2).ToString();

                            double dis2_x = MSS_cur_x - ATS_cur_x; // 현재 ATS와 현재 MSS 사이의 x 거리
                            double dis2_y = MSS_cur_y - ATS_cur_y; // 현재 ATS와 현재 MSS 사이의 y 거리

                            if (dis2 < 1) // 현재 ATS와 현재 MSS 위치 사이의 직선 거리가 1 pixel 미만일 경우 → 요격 성공
                            {
                                TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 시나리오 종료 \n";
                                TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 공중위협 요격 성공! \n";
                                wc.done();
                                //TbLog.Text += "--------------------------------------------  \n";
                                break;
                            }
                            else if (-diss < dis2_x && dis2_x < diss && -diss < dis2_y && dis2_y < diss) // 현재 ATS와 현재 MSS 사이의 x 거리와 y 거리가 지정된 pixel 값 미만일 경우 → 요격 성공 (현재 2 pixel로 설정)
                            {
                                TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 시나리오 종료 \n";
                                TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 공중위협 요격 성공 \n";
                                wc.done();
                                //TbLog.Text += "--------------------------------------------  \n";
                                break;
                            }

                            if (ATSX1.Text == "")
                            {
                                ATS_current_x.Text = "";
                                ATS_current_y.Text = "";
                                break;
                            }
                        }
                    }

                    Cv2.Resize(mat1, mat2, new OpenCvSharp.Size(1000, 800)); // 이미지 Resize
                    Bitmap bitimg = MatToBitmap(mat2); // 이미지 bitmap 변환
                    mapImage.Source = BitmapToImageSource(bitimg);

                    if (ATS_init_x < ATS_target_x) // 좌측에서 우측으로 날아가는 경우
                    {
                        ATS_cur_x += 1;
                    }
                    else if (ATS_init_x > ATS_target_x) // 우측에서 좌측으로 날아가는 경우
                    {
                        ATS_cur_x -= 1;
                    }

                    Cv2.WaitKey(30);

                    if (command == "pause")
                    {
                        while (Cv2.WaitKey(1) != 27)
                        {
                            if (command == "restart") break;
                        }
                    }

                }
            }
        }

        private void restart_LostMouseCapture(object sender, MouseEventArgs e) //재시작 버튼
        {
            wc.restart();
            if (pause.IsActive == true)
            {
                command = "restart";
                pause.IsActive = false;
                pause.IsEnabled = true;
                TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 시나리오 재시작 \n";
            }
        }
        private void Func()
        {
            wc.Init();
        }


        private void pause_LostMouseCapture(object sender, MouseEventArgs e) //일시정지 버튼
        {
            wc.pause();
            if (ATSX1.Text != "" && ATSX2.Text != "" && ATSY1.Text != "" && ATSY2.Text != "" && MSSX.Text != "" && MSSY.Text != "")
            {
                command = "pause";
                ScenarioStart.IsActive = true;
                ScenarioStart.IsEnabled = false;
                pause.IsActive = true;
                pause.IsEnabled = false;
                TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 시나리오 일시정지 \n";
            }
        }

        private void Launch_button_LostMouseCapture(object sender, MouseEventArgs e)//발사 버튼
        {
            wc.launch();
            if (pause.IsActive != true)
            {
                command2 = "launch";
                TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + " 유도탄 발사 \n";
            }
        }

        private string command; // openCV 명령어
        private string command2;

        private void deploy_LostMouseCapture(object sender, MouseEventArgs e)
        {
            command = "deploy";
            wc.deploy(Convert.ToInt64(ATSX1.Text), Convert.ToInt64(ATSY1.Text),
                Convert.ToInt64(ATSX2.Text), Convert.ToInt64(ATSY2.Text),
                Convert.ToInt64(MSSX.Text), Convert.ToInt64(MSSY.Text));
            TbLog.Text += System.DateTime.Now.ToString("hh:mm:ss.fff") + "시나리오 배포\n";
        }

        private void connectionCheck_LostMouseCapture(object sender, MouseEventArgs e)
        {
        }

        private void ATS_LostMouseCapture(object sender, MouseEventArgs e)
        {

        }
    }
}