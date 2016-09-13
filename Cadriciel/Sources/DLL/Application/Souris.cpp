///////////////////////////////////////////////////////////////////////////////
/// @file Souris.cpp
/// @author Luc Courbariaux
/// @date 2016-09-12
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


#include "Souris.h"
#include <AideGL.h>

#include "glm\glm.hpp"
#include <cmath>

using namespace aidegl;

Selection::Selection() {};

Selection* Selection::instance_{ nullptr };

Selection* Selection::obtenirInstance() {
	if (instance_ == nullptr) instance_ = new Selection;
	return instance_;
}

void Selection::libererInstance() {
	delete instance_;
	instance_ = nullptr;
}


void Selection::startClick(int x, int y) {
	X1 = x; Y1 = y;
	X2 = x; Y2 = y;
}

void Selection::currentClick(int x, int y) {
	initialiserRectangleElastique(glm::ivec2{ X1, Y1 }, 0x5555, 10);
	mettreAJourRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 }, glm::ivec2{ x, y });
	terminerRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ x, y });
	X2 = x; Y2 = y;
	
}

void Selection::endClick(int x, int y) {
	X2 = x; Y2 = y;
	if (pow(X1 - X2, 2) + pow(Y1 - Y2, 2) < 9) /* simple selection*/;
	else /* rectangle selection */;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////