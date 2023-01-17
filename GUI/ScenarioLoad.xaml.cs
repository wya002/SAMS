using Microsoft.WindowsAPICodePack.Dialogs;
using System;
using System.Collections.Generic;
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
            DirectoryInfo di = new DirectoryInfo("C:/Users/dndyd/OneDrive/문서");

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
            OnChildListInputEvent(xmlRead());
            Window.GetWindow(this).Close();
        }

        private void datagrid1_SelectedCellsChanged(object sender, System.Windows.Controls.SelectedCellsChangedEventArgs e)
        {
            DataRowView dataRow = (DataRowView)datagrid1.SelectedItem;
            string path = @"C:\Users\dndyd\OneDrive\문서" + "\\" + dataRow.Row.ItemArray[0].ToString() + ".xml";
            previewFile.Text = File.ReadAllText(path);
        }

        //XML 데이터 파싱
        private List<string> xmlRead()
        {
            //string temp = "";
            List<string> posValue = new List<string>();

            DataRowView dataRow = (DataRowView)datagrid1.SelectedItem;

            XmlTextReader reader = new(@"C:\Users\dndyd\OneDrive\문서" + "\\" + dataRow.Row.ItemArray[0].ToString() + ".xml");
            while (reader.Read())
            {
                switch (reader.NodeType)
                {
                    case XmlNodeType.Element: // The node is an element.
                        //temp += "<" + reader.Name;
                        while (reader.MoveToNextAttribute())
                        {
                            //temp += " " + reader.Name + "='" + reader.Value + "'";
                            if (reader.Value != "Value")
                            {
                                posValue.Add(reader.Value);
                            }
                        }
                        //temp += ">";
                        break;

                    case XmlNodeType.EndElement: //Display the end of the element.
                        //temp += "</" + reader.Name;
                        //temp += ">";
                        break;
                }
            }
            //MessageBox.Show(temp);
            return posValue;
        }
        //XML 파싱 데이터 넘기는 이벤트 핸들러
        public delegate void OnChildListInputHandler(List<string> Parameters);
        public event OnChildListInputHandler OnChildListInputEvent;

        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
