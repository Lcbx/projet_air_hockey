//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__


#include <windows.h>
#include <ctime>
#include <string>
#include "EtatOpenGL.h"
#include "../Configuration/ConfigTouches.h"
#include "../Configuration/ConfigJeu.h"
#include "../Configuration/ConfigDebug.h"
#include "../Configuration/ConfigProfils.h"
#include "../Tournoi.h"
#include "../AdaptateurJoueur.h"

class NoeudAbstrait;
class ArbreRenduINF2990;
class JoueurVirtuel;

namespace vue {
   class Vue;
}
///////////////////////////////////////////////////////////////////////////
/// @struct CoefficientConfiguration
/// @brief  Objet de transport des configurations
///
///	friction: Friction du sol (sans-unités)
/// rebond: Rebond des murs (sans-unités)
/// acceleration: Accélération des bonus vitesse (m/s)
/// 
///////////////////////////////////////////////////////////////////////////
struct CoefficientConfiguration{
	double friction;		//Friction du sol
	double rebond;			//Rebond des murs
	double acceleration;	//Accélération des bonus vitesse
} typedef CoefficientConfiguration;

const CoefficientConfiguration COEFFICIENTS_MINIMAUX = { 0, 0, 0 };
const CoefficientConfiguration COEFFICIENTS_DEFAULT = { 10, 0.8, 10 };
const CoefficientConfiguration COEFFICIENTS_MAXIMAUX = { 100, 1, 100 };

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une façade) sur l'ensemble
///        du modèle et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
	/// Obtient l'instance unique de la classe.
	static FacadeModele* obtenirInstance();
	/// Libère l'instance unique de la classe.
	static void libererInstance();

	/// Crée un contexte OpenGL et initialise celui-ci.
	void initialiserOpenGL(HWND hWnd);

	/// Charge la configuration à partir d'un fichier XML.
	void chargerConfiguration() const;
	/// Enregistre la configuration courante dans un fichier XML.
	void enregistrerConfiguration() const;

	/// Charge la zone de jeu à partir d'un fichier XML.
	void chargerZoneJeu(char* fichierZoneJeu) const;
	/// Enregistre la zone de jeu courante dans un fichier XML.
	void enregistrerZoneJeu(char* fichierZoneJeu) const;
	

	/// Accède à l'objet ConfigTouches
	ConfigTouches* getConfigTouches();

	/// Accède à l'objet ConfigProfils
	ConfigJeu* getConfigJeu();

	/// Accède à l'objet ConfigProfils
	ConfigDebug* getConfigDebug();

	/// Accède à l'objet ConfigProfils
	ConfigProfils* getConfigProfils();


	/// Libère le contexte OpenGL.
	void libererOpenGL();
	/// Affiche le contenu du modèle.
	void afficher() const;
	/// Affiche la base du contenu du modèle.
	void afficherBase() const;

	/// Retourne la vue courante.
	inline vue::Vue* obtenirVue();
	/// Retourne l'arbre de rendu.
	inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
	/// Retourne l'arbre de rendu.
	inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

	/// Retourne le tournoi en cours
	inline Tournoi<AdaptateurJoueur>* obtenirTournoi();
	/// Permet de créer le tournoi
	void creerTournoi(const char* nomZone, const int count, const char** nomsJoueurs, const bool* sontHumains, const char** nomProfils);
	/// Permet d'obtenir la configuration du tournoi
	void loadTournoi(char* nomZone, int count, char* nomsJoueurs, bool* sontHumains, char* nomProfils);

	/// Réinitialise la scène.
	void reinitialiser();

	/// Anime la scène.
	void animer(float temps);


   ///ajouter Bonus
	void ajouterBonus(int x, int y);

	///ajouter Portail
	void ajouterPortail(int x1, int y1);


	///ajouter second Portail
	void ajouterPortailDeux(int x2, int y2);
	

	///ajouter murets
	void ajouterMuret(int x1, int y1, int x2, int y2);
	
	///supprime le 1er Portail apres clic echap
	void supprimerDernierObjet();

	///retourner la pos X pour l'afficher dans la boite de configuration
	double getPosDataBidingX();

	///retourner la pos X pour l'afficher dans la boite de configuration
	double getPosDataBidingY();


	///effacer un objet selectionné de la table
	void effacerObjet();

	///deplacer un objet a partir des coordonnes de la boite de configuration
	void deplacerObjet(double x, double y, double angle, double scale);


	///retourner le nombre d'objet selectionne
	int nombreObjetSelectionne();


	///obtenir l'angle d'un objet
	double getAngle();

	///obtenir le scale d'un objet 
	double getScale();


	/// Permet d'obtenir les constantes de la zone de jeu (friction, rebond etc)
	CoefficientConfiguration getCoefficient() const;

	/// Permet de modifier les constantes de la zone de jeu (friction, rebond etc)
	void setCoefficient(CoefficientConfiguration coeff);

	///retourne si tous les objets sont dans la table
	bool objetEstDansLaTable();


	///initialiser la zone de jeu
	void initialiserScene();

	///ajouter les maillets et la rondelle a la zone
	void ajouterMailletEtRondelle();
	
	///enlever les maillets et la rondelle de la zone
	void retirerMailletEtRondelle();


	///permert de deplacer le maillet avec les touches de clavier
    void deplacerMailletAvecClavier(double x, double y);


	///Re initialiser la partie 
	void reinitialiserPartieCourante();

	///permert de deplacer le maillet avec la souris
	void deplacerMailletAvecSouris(double x, double y);

	/// Ali
	/// activer ou deactiver le rayon d'attraction des portails
	void activerRayonAttraction();
	void deactiverRayonAttraction();
	/// afficher ou effacer les points de controle
	void afficherPointControle();
	void effacerPointControle();
	///deplacer le maillet du jouer virtuel
	void ActiverJoueurVirtuel(double vitesse, double probabilite);
	// activer deactiver joueur virtuel
	void setjoueurVirtuel(bool activer);
	bool getjoueurVirtuel();
	double getVitesseVirtuel();
	void setVitesseVirtuel(double vitesse);
	double getProbabiliteVirtuel();
	void setProbabiliteVirtuel(double probabilite);
	// fonctions set/get des buts
	void setButDroite(bool but);
	void setButGauche(bool but);
	bool getButDroite();
	bool getButGauche();
	// fonctions get/set nombre de but pour gagner la partie
	int getNombreButs();
	bool setNombreButs(int nombre);
	// fonctions get/set pour activer/deactiver mode partierapide
	bool getPartieRapide();
	void setPartieRapide(bool activer);
	// activer/deactiver la rondelle - mettre en pause
	void activerRondelle();
	void deactiverRondelle();
	bool estEnPauseRondelle();
	/// Livrable 3
	std::string getNomJoueurCourant(int index);
	bool setNomJoueurCourant(std::string nom,int index);
	int getScoreCourant(int index);
	bool setScoreCourant(int score,int index);


	/// Ali
	/// Renvoie la constante contenant le nom du fichier de configuration
	//std::string getConfigFile();

private:

   /// Constructeur par défaut.
   FacadeModele() = default;
   /// Destructeur.
   ~FacadeModele();
   /// Constructeur copie désactivé.
   FacadeModele(const FacadeModele&) = delete;
   /// Opérateur d'assignation désactivé.
   FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Nom du fichier XML dans lequel doit se trouver la zone de jeu par défaut.
   static const std::string FICHIER_ZONEDEFAUT;

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;

   /// Poignée ("handle") vers la fenêtre où l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poignée ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poignée ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la scène.
   vue::Vue* vue_{ nullptr };
   /// Arbre de rendu contenant les différents objets de la scène.
   ArbreRenduINF2990* arbre_{ nullptr };

   /// Arthur
   /// Configuration des touches
   ConfigTouches _configTouches;
   /// Configuration des options de jeu
   ConfigJeu _configJeu;
   /// Configuration des options de debug
   ConfigDebug _configDebug;
   /// Configuration des profils
   ConfigProfils _configProfils;



   /// Coefficients de configuration
   CoefficientConfiguration coeff_ = COEFFICIENTS_DEFAULT;

   

   /// Ali
   // Livrable 2
   /// joueur virtuel 
   bool joueurVirtuelActive_{false};
   double vitesseVirtuelle_{ 1. };
   double probabilite_{ 0.5 };
   // buts
   bool butDroite_{ false };
   bool butGauche_{ false };
   // partieRapide
   bool partieRapide_{ false };
   // nombre de but pour gagner la partie
   int nombreButsMax_{ 3 };
   // rondelle en pause ?
   bool rondelleEnPause_{ false };
   // Livrable 3
   /// nom et score des joueurs courants
   std::string nomJoueurCourant1_ = "Player1";
   std::string nomJoueurCourant2_ = "Player2";
   int scoreJoueurCourant1_{ 0 };
   int scoreJoueurCourant2_{ 0 };
   /// Ali

   // Tournoi pour le mode tournoi
   Tournoi<AdaptateurJoueur>* tournoi_;
};



////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est présentement utilisée pour
/// voir la scène.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la scène (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la scène (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}

inline Tournoi<AdaptateurJoueur>* FacadeModele::obtenirTournoi() {
	return tournoi_;
}


#endif // __APPLICATION_FACADEMODELE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
