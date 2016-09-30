///////////////////////////////////////////////////////////////////////////////
/// @file AjoutAccelerateur.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AjoutAccelerateur.h"
#include <FacadeModele.h>

#include <iostream>
void AjoutAccelerateur::operationShortClick() { std::cout << "hi"; FacadeModele::obtenirInstance()->ajouterBonus(X1(), Y1()); }
void AjoutAccelerateur::operationDragClick() {}