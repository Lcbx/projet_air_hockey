///////////////////////////////////////////////////////////////////////////////
/// @file Rotation.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "PointsControle.h"
#include "FacadeModele.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "../Vue/Vue.h"


void PointsControle::start(int x, int y) {

	//conversion en coordonnees comme utilisees
	glm::dvec3 pointClick(x, y, 0);  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, pointClick);

	//evite de selectionner quelque chose qui ne l'est pas
	noeud_ = PASDENOEUD;
	
	//la table
	auto table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable();
	
	//on itere a travers ses enfants
	for (int i = 0; i < table->obtenirNombreEnfants(); i++) {
		//le point de controle etudie
		auto Pcontrol = static_cast<NoeudPointControle*>(table->chercher(i));
		//son delta
		double delta; Pcontrol->getDelta(delta);
		// si on est à la bonne distance, est selectionne
		if (glm::distance(pointClick, glm::dvec3(Pcontrol->obtenirPositionRelative())) < 1, 2 * delta)
			noeud_ = i;
	}
}

void PointsControle::current(int x, int y) {
	//si on a un noeud selectionné
	if (noeud_ != PASDENOEUD) {
		//on le met au point ou est la souris
		glm::dvec3 pointClick(x, y, 0);  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, pointClick);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->chercher(noeud_)->assignerPositionRelative(pointClick);
	}
}

void PointsControle::end(int x, int y) {

}

void PointsControle::operationShortClick() {
	//DO something
}
void PointsControle::operationDragClick() {
	//DO something
}