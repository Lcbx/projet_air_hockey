///////////////////////////////////////////////////////////////////////////////
/// @file Duplication.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Duplication.h"

void Duplication::current(int x, int y) {
	visiteur_.duplicate( glm::vec3(x, y, 0.f) );
}
void Duplication::operationShortClick() {
	//DO something
}
void Duplication::operationDragClick() {
	//DO something
}