///////////////////////////////////////////////////////////////////////////////
/// @file Rotation.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "MiseEchelle.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn MiseEchelle::current(int x, int y)
///
/// utilise les donn�es du click pour r�aliser une mise a echelle
/// sur les objets couramment selectionn�s
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void MiseEchelle::current(int x, int y) {
	visiteur_.mettreEchelle(Y1() - y);
	Y1() = y;
}

void MiseEchelle::operationShortClick() {
	//DO something
}
void MiseEchelle::operationDragClick() {
	//DO something
}
