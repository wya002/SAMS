using Microsoft.WindowsAPICodePack.Dialogs;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Input;

namespace GUI
{
    /// <summary>
    /// ScenarioLoad.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class ScenarioLoad : Window
    {
        public ScenarioLoad()
        {
            InitializeComponent();
        }

        private void Menubutton_LostMouseCapture(object sender, MouseEventArgs e)
        {
            Window.GetWindow(this).Close();
        }

        private void Button_MouseEnter(object sender, MouseEventArgs e)
        {

        }

        private void Button_LostMouseCapture(object sender, MouseEventArgs e)
        {
            DirectoryInfo di = new DirectoryInfo("C:/Users/User/Scenario");

            DataTable dataTable = new DataTable();
            dataTable.Columns.Add("ScenarioName", typeof(string));

            foreach (FileInfo File in di.GetFiles("*.xml"))
            {
                dataTable.Rows.Add(new string[] { File.Name.Substring(0, File.Name.Length-4)}) ;
            }
            datagrid1.ItemsSource = dataTable.DefaultView;
        }
    }
}
