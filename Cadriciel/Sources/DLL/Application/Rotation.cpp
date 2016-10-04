///////////////////////////////////////////////////////////////////////////////
/// @file Rotation.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


#include "Rotation.h"



void Rotation::current(int x, int y) {
	visiteur_.rotate(Y1() - y);
	Y1() = y;
}

void Rotation::operationShortClick() {
	//DO something
}
void Rotation::operationDragClick() {
	//DO something
}
