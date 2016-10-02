///////////////////////////////////////////////////////////////////////////////
/// @file Loupe.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include<glm\glm.hpp>
#include "AideGL.h"

#include "Loupe.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "VueOrtho.h"
#include "Projection.h"
#include "ProjectionOrtho.h"
#include "Souris.h"
#include <iostream>

void Loupe::start(int x, int y) {
	StrategieSouris::start(x, y);
	//initialise les graphiques du rectangle elastique
	aidegl::initialiserRectangleElastique(glm::ivec2{ X1(), Y1() }, 0x5555, 10);
}

void Loupe::current(int x, int y) {
	//determine s'il y a besoin d'afficher le rectangle
	if (StrategieSouris::plusDe3px()) {
		//affichage usuel : efface l'ancien rectangle par le nouveau
		aidegl::mettreAJourRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X2(), Y2() }, glm::ivec2{ x, y });
		//regle le cas special du passage du clic au rectange elastique (qui laisse un rectangle d'affiché)
		if (!effacerDernierRectangle) aidegl::mettreAJourRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X1(), Y1() }, glm::ivec2{ X2(), Y2() });
		effacerDernierRectangle = true;
	}
	else {
		//regle le cas special du passage du rectange elastique au clic  (qui laisse un rectangle d'affiché)
		if (effacerDernierRectangle) {
			aidegl::mettreAJourRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X1(), Y1() }, glm::ivec2{ X2(), Y2() });
			effacerDernierRectangle = false;
		}
	}
	X2() = x; Y2() = y;
}

void Loupe::end(int x, int y) {
	//fin de l'affichage des rectangles, efface le dernier rectangle
	if (StrategieSouris::plusDe3px()) aidegl::terminerRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X2(), Y2() });
	else aidegl::terminerRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X1(), Y1() });
	StrategieSouris::end(x, y);

}


void Loupe::operationShortClick() {
	// Ne rien faire
	std::cout << "Position : (" << X1() << "," << Y1() << ")" << std::endl;
}

void Loupe::operationDragClick() {
	glm::ivec2 point1 = glm::ivec2(X1(), Y1());
	glm::ivec2 point2 = glm::ivec2(X2(), Y2());

	if (!Souris::obtenirInstance()->getAlt())
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(point1, point2);
	else 
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOutElastique(point1, point2);

}


