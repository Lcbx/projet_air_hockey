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
#include "AideGL.h"

#include "Selection.h"
#include "../VisiteurSelection.h"
#include <iostream>
#include "Souris.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn Selection::start(int x, int y)
///
/// d.bute la selection
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Selection::start(int x, int y) {
	StrategieSouris::start(x, y);
	//initialise les graphiques du rectangle elastique
	aidegl::initialiserRectangleElastique(glm::ivec2{ X1(), Y1() }, 0x5555, 10);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Rotation::current(int x, int y)
///
/// affiche s'il y a lieu le rectangle de selection
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Selection::current(int x, int y) {
	//determine s'il y a besoin d'afficher le rectangle
	if (StrategieSouris::plusDe3px()) {
		//affichage usuel : efface l'ancien rectangle par le nouveau
		aidegl::mettreAJourRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X2(), Y2() }, glm::ivec2{ x, y });
		//regle le cas special du passage du clic au rectange elastique (qui laisse un rectangle d'affich�)
		if (!effacerDernierRectangle) aidegl::mettreAJourRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X1(), Y1() }, glm::ivec2{ X2(), Y2() });
		effacerDernierRectangle = true;
	}
	else {
		//regle le cas special du passage du rectange elastique au clic  (qui laisse un rectangle d'affich�)
		if (effacerDernierRectangle) {
			aidegl::mettreAJourRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X1(), Y1() }, glm::ivec2{ X2(), Y2() });
			effacerDernierRectangle = false;
		}
	}
	X2() = x; Y2() = y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Rotation::end(int x, int y)
///
/// termine s'il y a lieu le rectangle de selection
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Selection::end(int x, int y) {
	//fin de l'affichage des rectangles, efface le dernier rectangle
	if (StrategieSouris::plusDe3px()) aidegl::terminerRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X2(), Y2() });
	else aidegl::terminerRectangleElastique(glm::ivec2{ X1(), Y1() }, glm::ivec2{ X1(), Y1() });
	StrategieSouris::end(x, y);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn Selection::operationShortClick()
///
/// lance les op�rations de selection correspocdant au click
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Selection::operationShortClick() {
	glm::ivec2 begin(X1(), Y1());
	glm::ivec2   end(X2(), Y2());

	SelectionState mode = SelectionState::DEFAULT;
	if (Souris::obtenirInstance()->getControl())
		mode = SelectionState::INVSELECT;

	SingletonSelection::instance()->selectionner(begin, end, mode);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Selection::operationDragClick()
///
/// lance les op�rations de selection correspocdant au click
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Selection::operationDragClick() {
	operationShortClick();
}
