using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique.Utility
{
    public static class Utility
    {
        public static char[] ToCCharArray(this String str) {
            return Encoding.ASCII.GetChars(Encoding.ASCII.GetBytes(str + '\0'));
        }
    }
}
