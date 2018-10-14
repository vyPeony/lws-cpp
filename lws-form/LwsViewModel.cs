using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reactive.Disposables;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using Prism.Mvvm;
using Reactive.Bindings;

namespace lws_form
{
    public class LwsViewModel : BindableBase, IDisposable
    {
        private CompositeDisposable Disposable { get; } = new CompositeDisposable();
        public ReactiveCommand ExecuteCommand { get; } = new ReactiveCommand();
        public ReadOnlyReactiveCollection<EnchantData> Output { get; }

        public LwsViewModel()
        {
            model = new LwsModel();
            Output = model.Output.ToReadOnlyReactiveCollection();
            ExecuteCommand.Subscribe(_ => Execute());
            Disposable.Add(ExecuteCommand);
        }

        private LwsModel model = null;

        private void Execute()
        {
            model?.RunLwsCore();
        }

        public void Dispose()
        {
            Disposable.Dispose();
        }
    }
}
