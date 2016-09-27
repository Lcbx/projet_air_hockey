///////////////////////////////////////////////////////////////////////////////
/// @file AjoutPortail.h
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AjoutPortail.h"
#include "FacadeModele.h"
#include "Souris.h"

void AjoutPortail::start(int x, int y) {
	notrePosition_ = { x,y,x,y };
}

void AjoutPortail::current(int x, int y) {}

void AjoutPortail::end(int x, int y) {
	plusDe3px(notrePosition_) ? operationDragClick() : operationShortClick();
}

void AjoutPortail::position(int x, int y) {
	notrePosition_[2] = x; notrePosition_[3] = y;
}

void AjoutPortail::operationShortClick() {
	FacadeModele::obtenirInstance()->ajouterPortailDeux(notrePosition_[0], notrePosition_[1]);
	Souris::obtenirInstance()->EtatdelaSouris(Souris::DEBUT_AJOUT_PORTAIL);
}

void AjoutPortail::operationDragClick() {
	//DO something
}

void AjoutPortail::escEnfonce() {
	FacadeModele::obtenirInstance()->supprimerPortail(true);
	Souris::obtenirInstance()->EtatdelaSouris(Souris::DEBUT_AJOUT_PORTAIL);
}