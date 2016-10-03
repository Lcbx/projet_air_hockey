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
	//test du code de vérification de la table
	glm::dvec3 nouvPoint(x, y, 0);  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, nouvPoint);
	//std::cout << "click " << (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(nouvPoint) ? "dans La table\n" : " a l'exterieur de la table\n");
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->setPointControle(0,nouvPoint);
}

void PointsControle::current(int x, int y) {

}

void PointsControle::end(int x, int y) {

}

void PointsControle::operationShortClick() {
	//DO something
}
void PointsControle::operationDragClick() {
	//DO something
}