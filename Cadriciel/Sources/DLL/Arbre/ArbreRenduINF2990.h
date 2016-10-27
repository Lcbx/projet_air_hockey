///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"

#include <map>
#include <string>

#include "Noeuds/NoeudTypes.h"

///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui représente l'arbre de rendu spécifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilisés par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par défaut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu à son état initial.
   void initialiser();
   
	/// La chaîne représentant le type des araignées.
   static const std::string NOM_ARAIGNEE;
	/// La chaîne représentant le type des cones-cubes.
   static const std::string NOM_CONECUBE;
    /// La chaîne représentant le type des BONUS.
   static const std::string NOM_BONUS;
    /// La chaîne représentant le type des PORTAIl.
   static const std::string NOM_PORTAIL;
    /// La chaîne représentant le type des MURET.
   static const std::string NOM_MURET;
    /// La chaîne représentant le type des Tables
   static const std::string NOM_TABLE;
    /// La chaîne représentant le type des rondelles
   static const std::string NOM_RONDELLE;
    /// La chaîne représentant le type des point de control de la table
   static const std::string NOM_POINTCONTROLE;
   /// La chaîne représentant le type des MAILLET.
   static const std::string NOM_MAILLET;

   ///ajouter la table
   void ArbreRenduINF2990::ajouterTable();
   ///get le noeud table -- pas fini
   NoeudTable* ArbreRenduINF2990::getTable();

   ///ajouter le bonus accelerateur
   void ajouterBonus(glm::dvec3 position);
   ///ajouter le premier portail
   void ajouterPortail(glm::dvec3 position);
   ///ajoute 2eme portail
   void ajouterPortailDeux(glm::dvec3 position);
   ///ajouter le muret dans la table
   void ajouterMuret(glm::dvec3 position1, glm::dvec3 position2);

   bool premierEstajoute = false;

   /// fonction de calcul valable pour les ligne et murs
   GLfloat calculerScale(glm::dvec3 pos, glm::dvec3 posf);
   double calculerAngle(glm::dvec3 pos, glm::dvec3 posf);
   
   ///obtenir la position x d'un objet
   double getPosiX();
   ///obtenir la position y d'un objet
   double getPosiY();
   ///configurer un objet 
   void deplacerObjet(glm::dvec3 posDep, double angle, double scale);
   ///retourner le nombre d'objets selectionnées sur la table 
   int obtenirNombreObjetSelctionnes();
   ///obtenir l'angle d'un objet selectionné
   double getAngleDataBinding();
   ///obtenir le scale d'un objet selectionne
   double getScaleDataBinding();


   ///un compteur d'objets
   int compteur ;

   ///determiner si un objet dans la table
   bool objetEstDansLaTable();

	///determiner si la position est dans la table
   bool estInterieur = false;

   ///mettre les maillets et la rondelle sur la table
   void  ajouterMailletEtRondelle();

   ///permert de deplacer le maillet avec les touches de clavier
   void deplacerMailletAvecClavier(double x, double y);


   ///Re initialiser la partie courante 
  void reinitialiserPartieCourante();

  ///deplacer avec souris
  void deplacerMailletAvecSouris(glm::dvec3 pos);

  ///activer ou deactiver le rayon d'attraction d'un portail
  void activerRayonPortail();
  void deactiverRayonPortail();
  /// afficher ou effacer les points de controle
  void afficherPointControle();
  void effacerPointControle();

  int getScoreMoi() { return scoreMoi_; }
  void setScoreMoi(int scoreMoi) { scoreMoi_ = scoreMoi; }

  int getScoreAutre() { return scoreAutre_; }
  void setScoreAutre(int scoreAutre) { scoreAutre_ = scoreAutre; }

private :
	NoeudTable* noeudTable_;
	int scoreMoi_;
	int scoreAutre_;
};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
