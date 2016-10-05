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


////////////////////////////////////////////////////////////////////////
///
/// @fn Duplication::start(int x, int y)
///
/// debute la duplication en dédoublant les objets selectionnés
/// avec le visiteur duplication autour du curseur
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Duplication::start(int x, int y) {
	glm::dvec3 ancPoint; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, ancPoint);
	visiteur_.duplicate(ancPoint);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn Duplication::current(int x, int y)
///
/// actualise la position des clones en les déplaçant autour du curseur
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Duplication::current(int x, int y) {
	glm::dvec3 nouvPoint; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, nouvPoint);
	visiteur_.actualise(nouvPoint);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn Duplication::end(int x, int y)
///
/// finit la duplication en laisssant les clones là ou ils sont
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Duplication::end(int x, int y) {
	visiteur_.finalise();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn Duplication::escEnfonce()
///
/// annule la duplication en cours
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Duplication::escEnfonce() {
	visiteur_.supprimerClones();
}

void Duplication::operationShortClick() {
	//DO something
}
void Duplication::operationDragClick() {
	//DO something
}