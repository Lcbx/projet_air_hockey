#include <iostream>
#include "VisiteurSelection.h"
#include "Vue.h"
#include "Utilitaire.h"

///TODO: REFACTOR

struct BoudingBox {

};
bool SelectionInsideBoundingBox();

void VisiteurSelection::visiter(NoeudAbstrait* noeud) { }

void VisiteurSelection::visiter(NoeudComposite* noeud) {
	for (int i = 0, i_max = noeud->obtenirNombreEnfants(); i < i_max; i++)
		noeud->chercher(i)->accepter(this);
}


void VisiteurSelection::visiter(NoeudRondelle* noeud) { }

void VisiteurSelection::visiter(NoeudMuret* noeud) { }

void VisiteurSelection::visiter(NoeudBonus* noeud) {
	utilitaire::calculerBoiteEnglobante(*(noeud->getModele()));
	_begin - _end;
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
	for (auto node : x) {
		std::cout << "Hello world" << std::endl;
	}
}