///////////////////////////////////////////////////////////////////////////////
/// @file AjoutAccelerateur.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AjoutAccelerateur.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"
#include "../../Commun/Utilitaire/Vue/Vue.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn AjoutAccelerateur::operationShortClick()
///
/// ajoute un bonus accelerateur a la position du click simple,
/// pourvu que ce soit dans la zone de jeu.
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void AjoutAccelerateur::operationShortClick() {
	glm::dvec3 pointClick;  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), pointClick);
	//ajoute le bonus et le recupere (dernier enfant ajouté)
	FacadeModele::obtenirInstance()->ajouterBonus(X1(), Y1());
	auto bonus = (NoeudBonus*) FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants() - 1);
	//test le long du segment s'il est dans la table
	bool garder = true;
	glm::dvec3 debut = bonus->obtenirDroiteDirectrice().lirePoint();
	glm::dvec3 fin = debut + bonus->obtenirDroiteDirectrice().lireVecteur();
	//tout les 2 pixels
	double length = 0.5 * glm::distance(debut, fin);
	glm::dvec3 vec = (fin - debut) / length;
	for (int i = 1; i < length; i++) {
		debut += vec;
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(debut))
			garder = false;
	}
	if(!garder) FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer((NoeudAbstrait*)bonus);
}
void AjoutAccelerateur::operationDragClick() {}