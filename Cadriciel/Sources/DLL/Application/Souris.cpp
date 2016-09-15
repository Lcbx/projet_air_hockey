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
	//initialisation du clic
	X1 = x; Y1 = y;
	X2 = x; Y2 = y;
	//initialise les graphiques du rectangle elastique
	initialiserRectangleElastique(glm::ivec2{ X1, Y1 }, 0x5555, 10);
}

void Selection::currentClick(int x, int y) {
	//determine s'il y a besoin d'afficher le rectangle
	if (rectangleSelection()) {
		/* rectangle selection */
		//affichage usuel : efface l'ancien rectangle par le nouveau
		mettreAJourRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 }, glm::ivec2{ x, y });
		//regle le cas special du passage du clic au rectange elastique (qui laisse un rectangle d'affiché)
		if(!effacerDernierRectangle) mettreAJourRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 });
		effacerDernierRectangle = true;
	}
	else {
		/* simple selection*/
		//regle le cas special du passage du rectange elastique au clic  (qui laisse un rectangle d'affiché)
		if (effacerDernierRectangle) {
			mettreAJourRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 });
			effacerDernierRectangle = false;
		}
	}
	X2 = x; Y2 = y;
}

void Selection::endClick(int x, int y) {
	//fin de l'affichage des rectangles, efface le dernier rectangle
	terminerRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 }); 
	X2 = x; Y2 = y;
	//le code réel de la sélection
	if (rectangleSelection()) {

	}
	else {
			
	}
}

bool Selection::rectangleSelection() {
	return (X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2) > 9;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////