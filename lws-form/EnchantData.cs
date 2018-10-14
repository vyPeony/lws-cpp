using Prism.Mvvm;
using System;

namespace lws_form
{
    public class EnchantData : BindableBase
    {
        public EnchantData(string[] input)
        {
            if (input == null || input.Length != 6)
                throw new ArgumentException();

            Id = input[0];
            Page = input[1];
            Name = input[2];
            Enc = input[3];
            Power = input[4];
            Blood = input[5];
        }
        public string Id { get; set; }
        public string Page { get; set; }
        public string Name { get; set; }
        public string Enc { get; set; }
        public string Power { get; set; }
        public string Blood { get; set; }
    }
}
