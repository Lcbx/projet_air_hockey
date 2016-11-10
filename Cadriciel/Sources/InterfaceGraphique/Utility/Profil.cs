using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

namespace InterfaceGraphique
{
    public class Profil : System.ComponentModel.Component
    {
        private string nom_;
        private double vitesse_;
        private double probaDAgirPassivemnt_;

		
		/////////////////////////////////////////////////////////////////////////
        /// @fn public string Nom
        /// 
        /// @brief return le nom du profil
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////
        public string Nom {
            get { return this.getNomProfil(); }
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public Profil()
        /// 
        /// @brief Constructeur par defaut de la classe Profil
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        ////////////////////////////////////////////////////////////////////////////////////////
        public Profil()
        {
            nom_ = "defaut";
            vitesse_ = 10;
            probaDAgirPassivemnt_ = 0.2;
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public Profil(string nom, double vitesse, double facileABattre)
        /// 
        /// @brief Constructeur par paramètre de la classe Profil
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        public Profil(string nom, double vitesse, double facileABattre)
        {
            nom_ = nom;
            vitesse_ = vitesse;
            probaDAgirPassivemnt_ = facileABattre;
        }

	  
		/////////////////////////////////////////////////////////////////////////
        /// @fn public override string ToString() 
        /// 
        /// @brief return le nom du profil
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////
        public override string ToString()
        {
            return nom_;
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public string getNomProfil() 
        /// 
        /// @brief return le nom du profil
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////
        public string getNomProfil() 
        {
            return nom_ ;
        }
		
		/////////////////////////////////////////////////////////////////////////
        /// @fn public double getVitesseProfil() 
        /// 
        /// @brief cette fonction permet d'obtenir la vitesse du maillet du profil 
        /// 
        /// @param[in] aucun
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public double getVitesseProfil()
        {
            return vitesse_ ;
        }
		
		/////////////////////////////////////////////////////////////////////////
        /// @fn public double getProbProfil()
        /// 
        /// @brief cette fonction permet d'obtenir la probabilité d'agir passivement du profil 
        /// 
        /// @param[in] aucun
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public double getProbProfil()
        {
           return probaDAgirPassivemnt_ ;
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public double setNomProfil(string nom)
        /// 
        /// @brief cette fonction assigne un nom au profil 
        /// 
        /// @param[in] nom
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void setNomProfil(string nom)
        {
            nom_ = nom;
        }
		
		/////////////////////////////////////////////////////////////////////////
        /// @fn public double setVitesseProfil(double vitesse)
        /// 
        /// @brief cette fonction assigne une vitesse au maillet du profil 
        /// 
        /// @param[in] vitesse
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void setVitesseProfil(double vitesse)
        {
            vitesse_ = vitesse;
        }
		
		/////////////////////////////////////////////////////////////////////////
        /// @fn public double setProbProfil(double p)
        /// 
        /// @brief cette fonction assigne la probabilité d'agir passivement au profil 
        /// 
        /// @param[in] la probabilité d'agir passivement 
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void setProbProfil(double p)
        {
            probaDAgirPassivemnt_ = p;
        }

        /// @fn static public List<Profil> obtenirListeNomsProfils() 
        /// @brief Permet d'obtenir la liste des profils
        /// @return La liste des profils en mémoire contenant seulement les noms
        static public List<Profil> obtenirListeNomsProfils() { // TODO: Refactor
            int nbCharacteresProfils = FonctionsNatives.obtenirNombreProfils();
            int[] profils = new int[nbCharacteresProfils];
            FonctionsNatives.obtenirListeProfils(profils);
            string nomsProfils = new string(profils.Select(x => (char)x).ToArray());
            Regex reg = new Regex("\\#\\?&");
            nomsProfils = reg.Replace(nomsProfils, "\0");
            List<Profil> ret = new List<Profil>(nomsProfils.Split('\0').Where(x => x.Length != 0).Select(x => new Profil(x, 0, 0)).ToList());
            ret.Insert(0, new Profil());
            return ret;
        }
    }
}
