///////////////////////////////////////////////////////////////////////////////
/// @file DebutAjoutPortail.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "DebutAjoutPortail.h"
#include "FacadeModele.h"
#include "Souris.h"


void DebutAjoutPortail::operationShortClick() {
	FacadeModele::obtenirInstance()->ajouterPortail(X1(), Y1());
	Souris::obtenirInstance()->EtatdelaSouris(Souris::AJOUT_PORTAIL);
}
void DebutAjoutPortail::operationDragClick() {
	//DO something
}
