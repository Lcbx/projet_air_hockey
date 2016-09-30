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
#include "Vue.h"
#include "VueOrtho.h"
#include "Projection.h"
#include "ProjectionOrtho.h"
#include <iostream>



void Loupe::operationShortClick() {
	// Test d'Arthur
/*	std::cout << "Test SourisLoupe 1" << std::endl;
	FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	std::cout << "Test SourisLoupe 2" << std::endl;*/
	/*glm::ivec2* point1 = new glm::ivec2(X1(), Y1());
	FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(*point1, *point1);*/
}
void Loupe::operationDragClick() {

	std::cout << "Test Zoom�lastique 1" << std::endl;
	glm::ivec2* point1 = new glm::ivec2(X1(),Y1());
	glm::ivec2* point2 = new glm::ivec2(X2(), Y2());
	FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(*point1,*point2);
	std::cout << "Test Zoom�lastique 2" << std::endl;
}


