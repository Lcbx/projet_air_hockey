namespace InterfaceGraphique
{
    public class Profil : System.ComponentModel.Component
    {
        private string nom_;
        private double vitesse_;
        private double probaDAgirPassivemnt_;

        public Profil()
        {
            nom_ = "joueur virtuelle";
            vitesse_ = 10;
            probaDAgirPassivemnt_ = 2;
        }

        public Profil(string nom, double vitesse, double facileABattre)
        {
            nom_ = nom;
            vitesse_ = vitesse;
            probaDAgirPassivemnt_ = facileABattre;
        }

        public override string ToString()
        {
            return nom_;
        }
    }
}
