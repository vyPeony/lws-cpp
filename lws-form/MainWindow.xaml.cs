using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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

namespace lws_form
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("lws-core.dll", EntryPoint = "Debug")]
        public static extern void Debug();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var buffer = new System.IO.MemoryStream();
            var writer = new System.IO.StreamWriter(buffer);

            // Console に対する出力があるたびに、データを MemoryStream へ強制的に出力する
            writer.AutoFlush = true;

            Console.SetOut(writer);

            Debug();

            // ストリームの読み書き位置を先頭に戻す
            writer.BaseStream.Seek(0, System.IO.SeekOrigin.Begin);
            var reader = new System.IO.StreamReader(buffer);
            logText.Text = reader.ReadToEnd();

            reader.Close();
            writer.Close();
        }
    }
}
