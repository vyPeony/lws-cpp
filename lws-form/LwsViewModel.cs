using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Reactive.Disposables;
using System.Linq;
using System.Collections.ObjectModel;

namespace lws_form
{
    public enum WeaponType
    {
        Melee = 0,
        Ranged
    }

    public class LwsViewModel : BindableBase, IDisposable
    {
        private LwsModel model = null;
        private CompositeDisposable Disposable { get; } = new CompositeDisposable();
        public ReactiveCommand ExecuteCommand { get; } = new ReactiveCommand();
        public ReactiveCommand ExitCommand { get; } = new ReactiveCommand();
        public ReactiveProperty<int> SelectedGroupIndex { get; set; } = new ReactiveProperty<int>();
        public ReactiveProperty<int> SelectedNameIndex { get; set; } = new ReactiveProperty<int>();
        public ReactiveProperty<string> StartID { get; set; } = new ReactiveProperty<string>("0");
        public ReactiveProperty<string> EndID { get; set; } = new ReactiveProperty<string>("100000000");
        public ReactiveProperty<string> Threshold { get; set; } = new ReactiveProperty<string>("541");
        public ReactiveProperty<string> Level { get; set; } = new ReactiveProperty<string>("1");
        public ReactiveProperty<WeaponType> WeaponType { get; set; } = new ReactiveProperty<WeaponType>(lws_form.WeaponType.Melee);
        public ReactiveCollection<string> EnchantGroupList { get; set; } = new ReactiveCollection<string>();
        public ReactiveCollection<string> EnchantNameList { get; set; } = new ReactiveCollection<string>();
        public ReadOnlyReactiveCollection<EnchantData> Output { get; }

        public LwsViewModel()
        {
            model = new LwsModel();

            Output = model.Output.ToReadOnlyReactiveCollection();
            EnchantGroupList.AddRange(Const.EnchantmentList.Select(item => item.Name));

            ExecuteCommand.Subscribe(_ => Execute());
            ExitCommand.Subscribe(_ => Exit());

            SelectedGroupIndex.Subscribe(_ =>
            {
                EnchantNameList.Clear();
                EnchantNameList.AddRange(GetEnchantNameList().Select(i => i.Name));
                SelectedNameIndex.Value = 0;
            });

            Disposable.Add(Output);
            Disposable.Add(ExecuteCommand);
            Disposable.Add(ExitCommand);
        }

        private void Execute()
        {
            var param = new CoreParameter();
            param.EnchantmentID = GetEnchantNameList()[SelectedNameIndex.Value].ID;
            param.EnchantmentPowerThreshold = Convert.ToInt32(Threshold.Value);
            param.BeginID = Convert.ToInt32(StartID.Value);
            param.EndID = Convert.ToInt32(EndID.Value);
            param.WeaponType = (Int32)WeaponType.Value;
            param.Level = Convert.ToInt32(Level.Value);
            model?.RunLwsCore(param);
        }
        private void Exit()
        {
            model?.KillCoreProcess();
        }


        public void Dispose()
        {
            Disposable.Dispose();
        }

        public Enchantment[] GetEnchantNameList()
        {
            switch(SelectedGroupIndex.Value)
            {
                case 0:
                    return Const.EnchantmentDetailList_1;
                case 1:
                    return Const.EnchantmentDetailList_2;
                case 2:
                    return Const.EnchantmentDetailList_3;
                case 3:
                    return Const.EnchantmentDetailList_4;
                case 4:
                    return Const.EnchantmentDetailList_5;
                case 5:
                    return Const.EnchantmentDetailList_Extra;
                default:
                    return null;
            }
        }
    }
}
