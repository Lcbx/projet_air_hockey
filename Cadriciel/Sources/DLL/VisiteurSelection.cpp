#include <iostream>
#include "VisiteurSelection.h"
#include "Vue.h"
#include <algorithm>

///TODO: REFACTOR

////////////////////////////////////////////////////////////////////////////////
/// @func bool PointInsideBoundingBox
/// @param[in] selectionRectangle Rectangle de sélection
/// @param[in] point Point à vérifier s'il est dans la bounding box
/// @return Vrai si l'élément est sélectionné, autrement faux
////////////////////////////////////////////////////////////////////////////////
bool PointInsideBoundingBox(utilitaire::BoiteEnglobante selectionRectangle, glm::dvec3 point) {
	return (min(selectionRectangle.coinMin.x, selectionRectangle.coinMax.x) <= point.x &&
		max(selectionRectangle.coinMin.x, selectionRectangle.coinMax.x) >= point.x &&
		min(selectionRectangle.coinMin.y, selectionRectangle.coinMax.y) <= point.y &&
		max(selectionRectangle.coinMin.y, selectionRectangle.coinMax.y) >= point.y);
}

////////////////////////////////////////////////////////////////////////////////
/// @func bool SelectionInsideBoundingBox
/// @param[in] selectionRectangle Rectangle de sélection
/// @param[in] selectedObject Objet que l'on vérifie si il est sélectionné
/// @return Vrai si l'élément est sélectionné, autrement faux
/// TODO: Trouver un meilleur nom
/// Permet de vérifier si l'objet donné est situé dans la BoiteEnglobante
////////////////////////////////////////////////////////////////////////////////
bool SelectionInsideBoundingBox(utilitaire::BoiteEnglobante selectionRectangle, utilitaire::BoiteEnglobante selectedObject) {
	//Trois cas
	//- selection dans selected
	//- selected dans selection
	//- selection overlap selected
	// Si un point est dans le selection, l'objet est sélectionné, même chose si la selection est dans le sélectionné

	// Selected dans selection
	if (PointInsideBoundingBox(selectionRectangle, selectedObject.coinMin) || PointInsideBoundingBox(selectionRectangle, selectedObject.coinMax)) {
		return true;
	// Selection dans selected 
	} else if (PointInsideBoundingBox(selectedObject, selectionRectangle.coinMin) || PointInsideBoundingBox(selectedObject, selectionRectangle.coinMax)) {
		return true;
	} else {
		return false;
	}
}


void VisiteurSelection::setNodeSelectedState(NoeudAbstrait* noeud, bool isInsideSelection) {
	if (isInsideSelection) {
		switch (_state) {
		case SelectionState::SELECT:
			noeud->assignerSelection(true);
			break;
		case SelectionState::INVSELECT:
			noeud->inverserSelection();
			break;
		case SelectionState::UNSELECT:
			noeud->assignerSelection(false);
			break;
		}
	}
	else {
		switch (_state) {
		case SelectionState::SELECT:
			noeud->assignerSelection(false);
			break;
		/*case SelectionState::INVSELECT:
			noeud->inverserSelection();
			break;
		case SelectionState::UNSELECT:
			noeud->assignerSelection(false);
			break;*/
		}
	}
}

void VisiteurSelection::visiter(NoeudAbstrait* noeud) { }

void VisiteurSelection::visiter(NoeudComposite* noeud) {
	for (int i = 0, i_max = noeud->obtenirNombreEnfants(); i < i_max; i++)
		noeud->chercher(i)->accepter(this);
}


void VisiteurSelection::visiter(NoeudRondelle* noeud) { }

void VisiteurSelection::visiter(NoeudMuret* noeud) { 
	BoiteCollision boundingBox = noeud->obtenirBoiteCollision();

	
	/*if (SelectionInsideBoundingBox(_boundingBox, boudingBox)) {

	}*/
}

void VisiteurSelection::visiter(NoeudBonus* noeud) {
	utilitaire::BoiteEnglobante boundingBox = utilitaire::calculerBoiteEnglobante(*(noeud->getModele()));
	boundingBox.coinMin += noeud->obtenirPositionRelative();
	boundingBox.coinMin.x += 10;
	boundingBox.coinMax += noeud->obtenirPositionRelative();
	boundingBox.coinMax.x += 10;

	setNodeSelectedState(noeud, SelectionInsideBoundingBox(_boundingBox, boundingBox));

	if (noeud->estSelectionne())
		this->selectionner(noeud);
}

void VisiteurSelection::visiter(NoeudMaillet* noeud) { }

void VisiteurSelection::visiter(NoeudPortail* noeud) { }

void SingletonSelection::selectionner(
	glm::ivec2 begin, 
	glm::ivec2 end, 
	SelectionState state) 
{
	glm::dvec3 d_begin;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(
		begin.x, begin.y, d_begin
	);
	
	glm::dvec3 d_end;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(
		end.x, end.y, d_end
	);

	visiteur.setBoundingBox(d_begin, d_end);
	visiteur.setSelectMode(state);

	auto x = visiteur.obtenir_selection();
	/*std::cout << d_begin.x << ":" << d_begin.y << ":" << d_begin.z << std::endl;
	std::cout << d_end.x << ":" << d_end.y << ":" << d_end.z << std::endl;*/
	for (auto node : x) {
		std::cout << "Selection detected" << std::endl;
	}
}
