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


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui repr�sente l'arbre de rendu sp�cifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilis�s par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par d�faut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu � son �tat initial.
   void initialiser();


	/// La cha�ne repr�sentant le type des araign�es.
   static const std::string NOM_ARAIGNEE;
	/// La cha�ne repr�sentant le type des cones-cubes.
   static const std::string NOM_CONECUBE;


   /// La cha�ne repr�sentant le type des BONUS.
   static const std::string NOM_BONUS;

   /// La cha�ne repr�sentant le type des PORTAIl.
   static const std::string NOM_PORTAIL;

   /// La cha�ne repr�sentant le type des MURET.
   static const std::string NOM_MURET;

   /// La cha�ne repr�sentant le type des Tables
   static const std::string NOM_TABLE;

   /// La cha�ne repr�sentant le type des rondelles
   static const std::string NOM_RONDELLE;

   /// La cha�ne repr�sentant le type des point de control de la table
   static const std::string NOM_POINTCONTROLE;

   // ajouter la table
   void ArbreRenduINF2990::ajouterTable();

   void ajouterBonus(glm::dvec3 position);
   void ajouterPortail(glm::dvec3 position);


   //supprime le 1er portail
   void supprimerPortail(bool escTouche);

   void ajouterPortailDeux(glm::dvec3 position);


   void ajouterMuret(glm::dvec3 position1, glm::dvec3 position2);

   bool premierEstajoute = false;




   // fonction de calcul valable pour les ligne et murs
   GLfloat calculerScale(glm::dvec3 pos, glm::dvec3 posf);
   double calculerAngle(glm::dvec3 pos, glm::dvec3 posf);

};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
