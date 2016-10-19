using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class Configuration : Form
    {
       private static MenuPrincipal menuPrincipal_;
        public Configuration()
        {
            InitializeComponent();
        }

       public void setMenuPrincipalConfig(MenuPrincipal menuPrincipal)
        {
           menuPrincipal_ = menuPrincipal;
       }
    }

}
