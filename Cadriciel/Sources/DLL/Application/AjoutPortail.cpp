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



void AjoutPortail::operationShortClick() {
	if (clickInitial) {
		FacadeModele::obtenirInstance()->ajouterPortail( X1(), Y1() );
		clickInitial = false;
	}
	else {
		FacadeModele::obtenirInstance()->ajouterPortailDeux( X1(), Y1() );
		clickInitial = true;
	}
}

void AjoutPortail::operationDragClick() {
	//DO something
}

void AjoutPortail::escEnfonce() {
	FacadeModele::obtenirInstance()->supprimerPortail(true);
	clickInitial = true;
}