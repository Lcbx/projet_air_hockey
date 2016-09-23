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
#include "Souris.h"

int& StrategieSouris::X1() { return Souris::obtenirInstance()->getPosition()[0]; }
int& StrategieSouris::Y1() { return Souris::obtenirInstance()->getPosition()[1]; }
int& StrategieSouris::X2() { return Souris::obtenirInstance()->getPosition()[2]; }
int& StrategieSouris::Y2() { return Souris::obtenirInstance()->getPosition()[3]; }

bool StrategieSouris::plusDe3px(glm::ivec4 pos) {
	return ((pos[0] - pos[2])*(pos[0] - pos[2]) + (pos[1] - pos[3])*(pos[1] - pos[3]) > 9);
}

bool StrategieSouris::plusDe3px() {
	return plusDe3px(Souris::obtenirInstance()->getPosition());
}

void StrategieSouris::start(int x, int y) {
	//initialisation du clic
	Souris::obtenirInstance()->getPosition() = {x,y,x,y};
}

void StrategieSouris::current(int x, int y) {}

void StrategieSouris::end(int x, int y) {
	//fin du clic
	X2() = x; Y2() = y;
	//opération
	plusDe3px() ? operationDragClick() : operationShortClick();
}

void StrategieSouris::position(int x, int y) {}