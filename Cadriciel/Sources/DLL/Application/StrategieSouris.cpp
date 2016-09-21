///////////////////////////////////////////////////////////////////////////////
/// @file Selection.cpp
/// @author Luc Courbariaux
/// @date 2016-09-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "StrategieSouris.h"

bool StrategieSouris::plusDe3px() {
	return (X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2) > 9;
}

void StrategieSouris::start(int x, int y) {
	//initialisation du clic
	X1 = x; Y1 = y;
	X2 = x; Y2 = y;
}

void StrategieSouris::current(int x, int y) {
	X2 = x; Y2 = y;
}

void StrategieSouris::end(int x, int y) {
	X2 = x; Y2 = y;
	//opération
	plusDe3px() ? operationDragClick() : operationShortClick();
}