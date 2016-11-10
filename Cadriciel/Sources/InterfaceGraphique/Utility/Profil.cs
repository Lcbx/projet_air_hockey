namespace InterfaceGraphique
{
    public class Profil : System.ComponentModel.Component
    {
        private string nom_;
        private double vitesse_;
        private double probaDAgirPassivemnt_;

        public string Nom {
            get { return this.getNomProfil(); }
        }

        public Profil()
        {
            nom_ = "defaut";
            vitesse_ = 10;
            probaDAgirPassivemnt_ = 0.2;
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

        public string getNomProfil() 
        {
            return nom_ ;
        }
        public double getVitesseProfil()
        {
            return vitesse_ ;
        }
        public double getProbProfil()
        {
           return probaDAgirPassivemnt_ ;
        }

        public void setNomProfil(string nom)
        {
            nom_ = nom;
        }
        public void setVitesseProfil(double vitesse)
        {
            vitesse_ = vitesse;
        }
        public void setProbProfil(double p)
        {
            probaDAgirPassivemnt_ = p;
        }
    }
}
