///////////////////////////////////////////////////////////////////////////////
/// @file Duplication.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Duplication.h"
#include "../Vue/Vue.h"
#include "FacadeModele.h"


void Duplication::start(int x, int y) {
	glm::dvec3 ancPoint; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, ancPoint);
	visiteur_.duplicate(ancPoint);
}
void Duplication::current(int x, int y) {
	glm::dvec3 nouvPoint; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, nouvPoint);
	visiteur_.actualise(nouvPoint);
}
void Duplication::end(int x, int y) {
	visiteur_.finalise();
}

void Duplication::escEnfonce() {
	visiteur_.supprimerClones();
}

void Duplication::operationShortClick() {
	//DO something
}
void Duplication::operationDragClick() {
	//DO something
}