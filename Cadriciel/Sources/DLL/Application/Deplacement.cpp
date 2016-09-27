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
#include <iostream>
#include <FacadeModele.h>


void Deplacement::start(int x, int y) {
	StrategieSouris::start(x, y);

	X1() = x; //coordonnées x intial
	Y1() = y; // coordonnées y initial
}

void Deplacement::end(int x, int y)
{
	StrategieSouris::end(x, y);

	X2() = x; Y2() = y;
}

void Deplacement::current(int x, int y)
{
	StrategieSouris::current(x, y);

}
void Deplacement::operationShortClick() {
	//DO something

}
void Deplacement::operationDragClick() {

	FacadeModele::obtenirInstance()->deplacerObjet(X1(), Y1(), X2(), Y2());
}
