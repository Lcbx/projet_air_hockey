///////////////////////////////////////////////////////////////////////////////
/// @file Loupe.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Loupe.h"
#include "FacadeModele.h"



void Loupe::operationShortClick() {
	FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection()->zoomIn();
}
void Loupe::operationDragClick() {
	//DO something
}


