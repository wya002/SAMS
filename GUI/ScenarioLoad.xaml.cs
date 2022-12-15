using Microsoft.WindowsAPICodePack.Dialogs;
using System;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Xml;
//using TCCLibrary;

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

        private void Button_LostMouseCapture_1(object sender, MouseEventArgs e)
        {
            //xmlRead();
            //Window.GetWindow(this).Close();
        }

        private void datagrid1_SelectedCellsChanged(object sender, System.Windows.Controls.SelectedCellsChangedEventArgs e)
        {
            DataRowView dataRow = (DataRowView)datagrid1.SelectedItem;
            string path = @"C:\Users\User\Scenario" + "\\" + dataRow.Row.ItemArray[0].ToString() + ".xml";
            previewFile.Text = File.ReadAllText(path);
        }

        /*private void xmlRead()
        {
            string temp = "";
            XmlDocument xml = new XmlDocument();
            DataRowView dataRow = (DataRowView)datagrid1.SelectedItem;
            try
            {
                xml.Load(@"C:\Users\User\Scenario" + "\\" + dataRow.Row.ItemArray[0].ToString() + ".xml");
                XmlNodeList xmlList = xml.SelectNodes("/Synario/SynarioStart");

                foreach (XmlNode xnl in xmlList)
                {
                    temp += xnl["SynarioStart"].InnerText;
                    temp += xnl["SynarioDestination"].InnerText;
                    temp += xnl["SynarioMSS"].InnerText;
                    //temp += xml.SelectSingleNode(Synari)
                }
                MessageBox.Show(temp);
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }*/
    }
}
