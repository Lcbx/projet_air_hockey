using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
   public class Profil

    {
        private string nom_;
        private float vitesse_;
        private bool probaDAgirPassivemnt_;

        public Profil()
        {
            nom_ = "joueur virtuelle";
            vitesse_ = 10;
            probaDAgirPassivemnt_ = true;
        }

        public Profil(string nom, float vitesse, bool facileABattre)
        {
            nom_ = nom;
            vitesse_ = vitesse;
            probaDAgirPassivemnt_ = facileABattre;
        }
    }
}
