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
#include "Souris.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"
#include "../../Commun/Utilitaire/Vue/Vue.h"




void AjoutPortail::operationShortClick() {
	glm::dvec3 pointClick;  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), pointClick);
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(pointClick)) {
		if (clickInitial) {
			FacadeModele::obtenirInstance()->ajouterPortail(X1(), Y1());
			clickInitial = false;
		}
		else {
			FacadeModele::obtenirInstance()->ajouterPortailDeux(X1(), Y1());
			clickInitial = true;
		}
	}
}

void AjoutPortail::operationDragClick() {
	//DO something
}

void AjoutPortail::escEnfonce() {
	FacadeModele::obtenirInstance()->supprimerPortail(true);
	clickInitial = true;
}