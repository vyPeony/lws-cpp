using Prism.Mvvm;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Text;

namespace lws_form
{
    public class CoreParameter
    {
        public int EnchantmentID;
        public int BeginID;
        public int EndID;
        public int EnchantmentPowerThreshold;
        public int Level;
        public int WeaponType;
    }

    class LwsModel : BindableBase
    {
        Process coreProcess = null;

        public ObservableCollection<EnchantData> Output = new ObservableCollection<EnchantData>();
        private bool skipped = false;

        public LwsModel()
        {
        }

        public void RunLwsCore(CoreParameter inParameter)
        {
            KillCoreProcess();

            Output.Clear();
            skipped = false;

            coreProcess = new Process();
            coreProcess.StartInfo.FileName = @"lws-core.exe";
            coreProcess.StartInfo.Arguments = $"--SearchType {inParameter.EnchantmentID} -t {inParameter.EnchantmentPowerThreshold} -b {inParameter.BeginID} -e {inParameter.EndID}";
            coreProcess.StartInfo.Arguments += $" -l {inParameter.Level} -w {inParameter.WeaponType}";
            coreProcess.StartInfo.Arguments += $"";
            coreProcess.StartInfo.CreateNoWindow = true;
            coreProcess.StartInfo.UseShellExecute = false;
            coreProcess.StartInfo.RedirectStandardOutput = true;
            coreProcess.StartInfo.StandardOutputEncoding = Encoding.UTF8;
            coreProcess.EnableRaisingEvents = true;
            coreProcess.Exited += (s, eargs) => 
            {

            };
            coreProcess.OutputDataReceived += new DataReceivedEventHandler(process_DataReceived);

            coreProcess.Start();
            coreProcess.BeginOutputReadLine();
        }

        void process_DataReceived(object sender, DataReceivedEventArgs e)
        {
            if (skipped)
            {
                if(e.Data != null && !e.Data.StartsWith("Id"))
                    Output.Add(new EnchantData(e.Data.Split(',')));
            }
            else
                skipped = true;
        }

        public void KillCoreProcess()
        {
            try
            {
                coreProcess?.Kill();
            }
            catch { }
        }
    }
}
