///////////////////////////////////////////////////////////////////////////////
/// @file Selection.cpp
/// @author Luc Courbariaux
/// @date 2016-09-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


#include<glm\glm.hpp>
#include "AideGL.h" //ne surtout pas bouger, crait une erreur si mis après freeglut

//#include <GL/freeglut.h>

#include "Selection.h"
#include "../VisiteurSelection.h"



void Selection::start(int x, int y) {
	StrategieSouris::start(x, y);
	//initialise les graphiques du rectangle elastique
	aidegl::initialiserRectangleElastique(glm::ivec2{ X1, Y1 }, 0x5555, 10);
}

void Selection::current(int x, int y) {
	//determine s'il y a besoin d'afficher le rectangle
	if (StrategieSouris::plusDe3px()) {
		//affichage usuel : efface l'ancien rectangle par le nouveau
		aidegl::mettreAJourRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 }, glm::ivec2{ x, y });
		//regle le cas special du passage du clic au rectange elastique (qui laisse un rectangle d'affiché)
		if (!effacerDernierRectangle) aidegl::mettreAJourRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 });
		effacerDernierRectangle = true;
	}
	else {
		//regle le cas special du passage du rectange elastique au clic  (qui laisse un rectangle d'affiché)
		if (effacerDernierRectangle) {
			aidegl::mettreAJourRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 });
			effacerDernierRectangle = false;
		}
	}
	StrategieSouris::current(x, y);
}

void Selection::end(int x, int y) {
	//fin de l'affichage des rectangles, efface le dernier rectangle
	if (StrategieSouris::plusDe3px()) aidegl::terminerRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 });
	else aidegl::terminerRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X1, Y1 });
	StrategieSouris::end(x, y);
}

bool Selection::controlPresse() {
	return false;//glutGetModifiers() == GLUT_ACTIVE_CTRL;
}

void Selection::operationShortClick() {
	glm::ivec2 begin(X1, Y1);
	glm::ivec2   end(X2, Y2);

	SingletonSelection::instance()->selectionner(begin, end);
}
void Selection::operationDragClick() {
}
