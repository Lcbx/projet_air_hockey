///////////////////////////////////////////////////////////////////////////////
/// @file AjoutAccelerateur.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AjoutAccelerateur.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"
#include "../../Commun/Utilitaire/Vue/Vue.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn AjoutAccelerateur::operationShortClick()
///
/// ajoute un bonus accelerateur a la position du click simple,
/// pourvu que ce soit dans la zone de jeu.
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void AjoutAccelerateur::operationShortClick() {
	glm::dvec3 pointClick;  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), pointClick);
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(pointClick))
		FacadeModele::obtenirInstance()->ajouterBonus(X1(), Y1());
}
void AjoutAccelerateur::operationDragClick() {}