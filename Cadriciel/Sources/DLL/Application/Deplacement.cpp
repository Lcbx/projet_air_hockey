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
#include "../VisiteurDeplacement.h"

void Deplacement::current(int x, int y) {
	VisiteurDeplacement(glm::vec3(x-X1(), Y1()-y, 0.f));
	X1() = x;
	Y1() = y;
}

void Deplacement::operationShortClick() {
	//DO something
}
void Deplacement::operationDragClick() {
	//DO something
}
