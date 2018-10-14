using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Reactive.Disposables;

namespace lws_form
{
    public class LwsViewModel : BindableBase, IDisposable
    {
        private LwsModel model = null;
        private CompositeDisposable Disposable { get; } = new CompositeDisposable();
        public ReactiveCommand ExecuteCommand { get; } = new ReactiveCommand();
        public ReadOnlyReactiveCollection<EnchantData> Output { get; }

        public LwsViewModel()
        {
            model = new LwsModel();
            Output = model.Output.ToReadOnlyReactiveCollection();
            ExecuteCommand.Subscribe(_ => Execute());

            Disposable.Add(Output);
            Disposable.Add(ExecuteCommand);
        }

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
