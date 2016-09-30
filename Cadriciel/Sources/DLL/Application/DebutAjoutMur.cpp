///////////////////////////////////////////////////////////////////////////////
/// @file DebutAjoutMur.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "DebutAjoutMur.h"
#include "Souris.h"

void DebutAjoutMur::operationShortClick() {
	Souris::obtenirInstance()->EtatdelaSouris(Souris::AJOUT_MUR);
}
void DebutAjoutMur::operationDragClick() {
	//DO something
}
