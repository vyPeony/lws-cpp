using Prism.Mvvm;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Text;

namespace lws_form
{
    class LwsModel : BindableBase
    {
        public ObservableCollection<EnchantData> Output = new ObservableCollection<EnchantData>();
        private bool skipped = false;

        public LwsModel()
        {
        }

        public void RunLwsCore()
        {
            Output.Clear();
            skipped = false;

            Process p = new Process();
            p.StartInfo.FileName = @"lws-core.exe";
            //p.StartInfo.Arguments =
            p.StartInfo.CreateNoWindow = true;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.StandardOutputEncoding = Encoding.UTF8;
            p.EnableRaisingEvents = true;
            p.Exited += (s, eargs) => 
            {

            };
            p.OutputDataReceived += new DataReceivedEventHandler(process_DataReceived);

            p.Start();
            p.BeginOutputReadLine();
        }

        void process_DataReceived(object sender, DataReceivedEventArgs e)
        {
            if (skipped)
            {
                if(e.Data != null)
                    Output.Add(new EnchantData(e.Data.Split(',')));
            }
            else
                skipped = true;
        }
    }
}
