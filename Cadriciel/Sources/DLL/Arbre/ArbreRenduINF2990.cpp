///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"
#include "Usines/UsineNoeud.h"
#include "EtatOpenGL.h"
#include "Noeuds/NoeudTypes.h"
#include <iostream>
#include "../Visiteur.h"
#include "../VisiteurAjout.h"
#include "../VisiteurDeplacement.h"
#include "../VisiteurMiseEchelle.h"
#include "../VisiteurRotation.h"
#include "../VisiteurSelection.h"

using namespace std;


/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La chaîne représentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };

//Rondelle
const std::string ArbreRenduINF2990::NOM_BONUS{ "bonus" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeud<NoeudAraignee>{ NOM_ARAIGNEE, std::string{ "media/spider.obj" } });
	ajouterUsine(NOM_CONECUBE, new UsineNoeud<NoeudConeCube>{ NOM_CONECUBE, std::string{ "media/cubecone.obj" } });
	ajouterUsine(NOM_BONUS, new UsineNoeud<NoeudBonus>{ NOM_BONUS, std::string{ "media/Rondelle.obj" } });
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();

	///TODO
	///Chabnger l'araignee par la table / cube par les buts

	/*
	// On ajoute un noeud bidon seulement pour que quelque chose s'affiche.
	NoeudAbstrait* noeudAraignee{ creerNoeud(NOM_ARAIGNEE) };
	noeudAraignee->assignerPositionRelative(glm::dvec3{ 0.0, 0.0, 0.0 });
	//noeudAraignee->ajouter(creerNoeud(NOM_CONECUBE));
	ajouter(noeudAraignee);
	
	*/

	
	/*NoeudAbstrait* noeudRondelle{ creerNoeud(NOM_RONDELLE) };
	ajouter(noeudRondelle);
	*/

	
	
}

void ArbreRenduINF2990::ajouterBonus(glm::dvec3 pos) 
{

	NoeudAbstrait* noeudBonus{ creerNoeud(NOM_BONUS) };
	Visiteur* v1 = new VisiteurAjout(glm::dvec3{50* pos.x, 50*pos.y, 0.0 });

	noeudBonus->accepter(v1);
	cout << "Bonus x  : " << noeudBonus->obtenirPositionRelative().x << "  Bonus  y: " << noeudBonus->obtenirPositionRelative().y << "  Bonus z: " << noeudBonus->obtenirPositionRelative().z << endl;



	// toujours liberer la mémoire !!!!
	delete v1;
	
/*
	VisiteurAjout* v1 = new VisiteurAjout();

	NoeudAbstrait* noeudBonus{ creerNoeud(NOM_BONUS) };

	noeudBonus->assignerPositionRelative(position);
	ajouter(noeudBonus);
	noeudBonus->accepter(v1);

	//tjrs supprimer pour ne pas avoir une fuite de memoire 
	delete v1;

	*/

	/*
	NoeudAbstrait* noeudRondelle{ creerNoeud(NOM_RONDELLE) };
	
	noeudRondelle->assignerPositionRelative(position);
	ajouter(noeudRondelle);
	*/
	
	std::printf("ARBRE RENDU 2990 \n ");
	
}





///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
