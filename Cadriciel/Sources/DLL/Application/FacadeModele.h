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

class NoeudAbstrait;
class ArbreRenduINF2990;

namespace vue {
   class Vue;
}
///////////////////////////////////////////////////////////////////////////
/// @struct CoefficientConfiguration
/// @brief  Objet de transport des configurations
///
///	friction: Friction du sol (sans-unit�s)
/// rebond: Rebond des murs (sans-unit�s)
/// acceleration: Acc�l�ration des bonus vitesse (m/s)
/// 
///////////////////////////////////////////////////////////////////////////
struct CoefficientConfiguration{
	double friction;		//Friction du sol
	double rebond;			//Rebond des murs
	double acceleration;	//Acc�l�ration des bonus vitesse
} typedef CoefficientConfiguration;

const CoefficientConfiguration COEFFICIENTS_MINIMAUX = { 0, 0, 0 };
const CoefficientConfiguration COEFFICIENTS_DEFAULT = { 10, 0.8, 10 };
const CoefficientConfiguration COEFFICIENTS_MAXIMAUX = { 100, 1, 100 };

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une fa�ade) sur l'ensemble
///        du mod�le et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
	/// Obtient l'instance unique de la classe.
	static FacadeModele* obtenirInstance();
	/// Lib�re l'instance unique de la classe.
	static void libererInstance();

	/// Cr�e un contexte OpenGL et initialise celui-ci.
	void initialiserOpenGL(HWND hWnd);
	/// Charge la configuration � partir d'un fichier XML.
	void chargerConfiguration() const;
	/// Enregistre la configuration courante dans un fichier XML.
	void enregistrerConfiguration() const;
	/// Charge la zone de jeu � partir d'un fichier XML.
	void chargerZoneJeu(char* fichierZoneJeu) const;
	/// Enregistre la zone de jeu courante dans un fichier XML.
	void enregistrerZoneJeu(char* fichierZoneJeu) const;
	/// Lib�re le contexte OpenGL.
	void libererOpenGL();
	/// Affiche le contenu du mod�le.
	void afficher() const;
	/// Affiche la base du contenu du mod�le.
	void afficherBase() const;

	/// Retourne la vue courante.
	inline vue::Vue* obtenirVue();
	/// Retourne l'arbre de rendu.
	inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
	/// Retourne l'arbre de rendu.
	inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

	/// R�initialise la sc�ne.
	void reinitialiser();

	/// Anime la sc�ne.
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


	///effacer un objet selectionn� de la table
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
	///deplacer le maillet du jouer virtuel selon le scenario defensif
	void virtuelDefensif();
	///
private:

   /// Constructeur par d�faut.
   FacadeModele() = default;
   /// Destructeur.
   ~FacadeModele();
   /// Constructeur copie d�sactiv�.
   FacadeModele(const FacadeModele&) = delete;
   /// Op�rateur d'assignation d�sactiv�.
   FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Nom du fichier XML dans lequel doit se trouver la zone de jeu par d�faut.
   static const std::string FICHIER_ZONEDEFAUT;

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;

   /// Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poign�e ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poign�e ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la sc�ne.
   vue::Vue* vue_{ nullptr };
   /// Arbre de rendu contenant les diff�rents objets de la sc�ne.
   ArbreRenduINF2990* arbre_{ nullptr };

   /// Coefficients de configuration
   CoefficientConfiguration coeff_ = COEFFICIENTS_DEFAULT;

};



////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est pr�sentement utilis�e pour
/// voir la sc�ne.
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
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
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
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}


#endif // __APPLICATION_FACADEMODELE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
