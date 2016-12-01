using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Utility
{
    /// @class NumericUpDownSafe 
    /// @brief Permet d'éviter les triggers causé par le changement programatique des valeurs
    /// @author Kevin
    /// @source http://stackoverflow.com/questions/2230454/c-sharp-set-usercontrol-value-without-invoking-the-valuechanged-event
    public class NumericUpDownSafe : NumericUpDown{
        EventHandler eventHandler = null;

        public new event EventHandler ValueChanged {
            add { eventHandler += value; base.ValueChanged += value; }
            remove { eventHandler -= value; base.ValueChanged -= value; }
        }

        public new decimal Value {
            get { return base.Value; }
            set { base.ValueChanged -= eventHandler; base.Value = value; base.ValueChanged += eventHandler; }
        }
    }
}
