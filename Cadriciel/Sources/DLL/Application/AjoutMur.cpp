///////////////////////////////////////////////////////////////////////////////
/// @file AjoutMur.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AjoutMur.h"
#include "FacadeModele.h"
#include "Souris.h"

void AjoutMur::start(int x, int y) {
	notrePosition_ = {x,y,x,y};
}

void AjoutMur::current(int x, int y) {
	notrePosition_[2] = x; notrePosition_[3] = y;
	FacadeModele::obtenirInstance()->ajouterMurFantome(X1(), Y1(), x, y);
}

void AjoutMur::end(int x, int y) {
	plusDe3px(notrePosition_) ? operationDragClick() : operationShortClick();
}

void AjoutMur::operationShortClick() {
	FacadeModele::obtenirInstance()->ajouterMuret(X1(), Y1(), notrePosition_[2], notrePosition_[3]);
	Souris::obtenirInstance()->EtatdelaSouris(Souris::DEBUT_AJOUT_MUR);
}

void AjoutMur::operationDragClick() {
	//DO something
}