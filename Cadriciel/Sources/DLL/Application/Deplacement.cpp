///////////////////////////////////////////////////////////////////////////////
/// @file Deplacement.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Deplacement.h"
#include "../VisiteurDeplacement.h"
#include "../Vue/Vue.h"
#include "FacadeModele.h"

void Deplacement::current(int x, int y) {
	glm::dvec3 nouvPoint; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, nouvPoint);
	glm::dvec3 ancPoint; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), ancPoint);
	VisiteurDeplacement( nouvPoint - ancPoint );
	X1() = x;
	Y1() = y;
}

void Deplacement::operationShortClick() {
	//DO something
}
void Deplacement::operationDragClick() {
	//DO something
}
