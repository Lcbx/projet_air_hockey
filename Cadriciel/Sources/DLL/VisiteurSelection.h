#pragma once
#ifndef VISITEUR_SELECTION_H
#define VISITEUR_SELECTION_H

#include <iostream>
#include <string>

#include "Visiteur.h"
#include <vector>

#include "glm/glm.hpp"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
///TODO: REFACTOR
enum SelectionState {
	SELECT, INVSELECT, UNSELECT
};

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelection
/// @brief Patron visiteur de la sélection
///
/// @author Wajdi Gharsalli
/// @date 2016-09-09
/// 
/// @author Carl-Vincent Landry-Duval
/// @date 2016-09-16
///////////////////////////////////////////////////////////////////////////
class VisiteurSelection : public Visiteur
{
	std::vector<NoeudAbstrait*> selectionnes;
	SelectionState _state = SelectionState::SELECT;

	glm::dvec3 _begin;
	glm::dvec3 _end;
	
public:
	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);

	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void selectionner(NoeudAbstrait*)
	///
	/// Permet de garder en sélection le noeud donné
	///
	/// @param[in] node Noeud à ajouter
	///
	/// @return Nothing
	///
	////////////////////////////////////////////////////////////////////////
	void selectionner(NoeudAbstrait* node) {
		selectionnes.push_back(node);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn setBoundingBox
	///
	/// Permet de changer le bounding box pour la sélection
	///
	/// @param[in] glm::dvec3 begin Point de début
	/// @param[in] glm::dvec3 end   Point de fin
	///
	/// @return Nothing
	///
	////////////////////////////////////////////////////////////////////////
	void setBoundingBox(glm::dvec3 begin, glm::dvec3 end) {
		_begin = begin; _end = end;
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn setSelectMode
	///
	/// Permet de changer le bounding box pour la sélection
	///
	/// @param[in] SelectionState state État de sélection
	///
	/// @return Nothing
	///
	////////////////////////////////////////////////////////////////////////
	void setSelectMode(SelectionState state) { 
		_state = state;
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn std::vector<NoeudAbstrait*> obtenir_selection()
	///
	/// Permet d'obtenir la liste des noeuds sélectionnés
	///
	/// @return Un vecteur des noeuds sélectionnés
	///
	////////////////////////////////////////////////////////////////////////
	std::vector<NoeudAbstrait*> obtenir_selection() { 
		selectionnes.clear();
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
		return selectionnes;
	};
};

///////////////////////////////////////////////////////////////////////////
/// @class Selection
/// @brief Patron singleton de visiteur de la sélection
///
/// @author Carl-Vincent Landry-Duval
/// @date 2016-09-09
///////////////////////////////////////////////////////////////////////////
class SingletonSelection : VisiteurSelection {
private:
	SingletonSelection() { };
	VisiteurSelection visiteur;

public:
	SingletonSelection(SingletonSelection& const) = delete;
	void operator=(SingletonSelection& const) = delete;

	static SingletonSelection *instance() {
		static SingletonSelection _instance;
		return &_instance;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn selectionner
	///
	/// Permet d'obtenir les objets sélectionnés dans le carré donné
	///
	/// @return Nothing
	///
	////////////////////////////////////////////////////////////////////////
	void selectionner(
		glm::ivec2 begin, 
		glm::ivec2 end, 
		SelectionState state = SelectionState::SELECT);
};
#endif
