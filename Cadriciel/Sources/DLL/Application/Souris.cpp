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
#include <FacadeModele.h>

#include "glm\glm.hpp"

using namespace aidegl;

Souris::Souris() {};

Souris* Souris::instance_{ nullptr };

Souris* Souris::obtenirInstance() {
	if (instance_ == nullptr) instance_ = new Souris;
	return instance_;
}

void Souris::libererInstance() {
	delete instance_;
	instance_ = nullptr;
}

void Souris::EtatdelaSouris(int etat){
	etatSouris = static_cast<Etats>(etat);
}

void Souris::startClick(int x, int y) {
	//initialisation du clic
	X1 = x; Y1 = y;
	X2 = x; Y2 = y;
	//initialise les graphiques du rectangle elastique
	if(etatSouris == SELECTION) initialiserRectangleElastique(glm::ivec2{ X1, Y1 }, 0x5555, 10);
}

void Souris::currentClick(int x, int y) {
	//determine s'il y a besoin d'afficher le rectangle
	if (etatSouris == SELECTION) {
		if (plusDe3px()) {
			/* rectangle selection */
			//affichage usuel : efface l'ancien rectangle par le nouveau
			mettreAJourRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 }, glm::ivec2{ x, y });
			//regle le cas special du passage du clic au rectange elastique (qui laisse un rectangle d'affiché)
			if (!effacerDernierRectangle) mettreAJourRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 });
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
	}
	X2 = x; Y2 = y;
}

void Souris::endClick(int x, int y) {
	//fin de l'affichage des rectangles, efface le dernier rectangle
	if(etatSouris == SELECTION && plusDe3px()) terminerRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X2, Y2 });
	else if(etatSouris == SELECTION) terminerRectangleElastique(glm::ivec2{ X1, Y1 }, glm::ivec2{ X1, Y1 });
	X2 = x; Y2 = y;
	//opération
	plusDe3px() ? operationDragClick() : operationShortClick();
}

bool Souris::plusDe3px() {
	return (X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2) > 9 ;
}


void Souris::operationShortClick() {
	switch (etatSouris) {
	case SELECTION: { break; }
	case LOUPE: { break; }
	case DEPLACEMENT: { break; }
	case ROTATION: { break; }
	case DUPLICATION: { break; }
	case AJOUT_ACCELERATEUR: { FacadeModele::obtenirInstance()->ajouterBonus(X1,Y1); break; }
	case DEBUT_AJOUT_MUR: { break; }
	case AJOUT_MUR: { break; }
	case DEBUT_AJOUT_PORTAIL: { break; }
	case AJOUT_PORTAIL: { break; }
	default: break;
	}
}

void Souris::operationDragClick() {
	switch (etatSouris) {
	case SELECTION: { break; }
	case LOUPE: { break; }
	case DEPLACEMENT: { break; }
	case ROTATION: { break; }
	case DUPLICATION: { break; }
	case AJOUT_ACCELERATEUR: {}
	case DEBUT_AJOUT_MUR: { break; }
	case AJOUT_MUR: { break; }
	case DEBUT_AJOUT_PORTAIL: { break; }
	case AJOUT_PORTAIL: { break; }
	default: break;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////