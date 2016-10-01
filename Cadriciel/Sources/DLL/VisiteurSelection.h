#pragma once
#ifndef VISITEUR_SELECTION_H
#define VISITEUR_SELECTION_H

#include <iostream>
#include <string>

#include "Visiteur.h"
#include <vector>

#include "Utilitaire.h"

#include "glm/glm.hpp"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
///TODO: REFACTOR
enum SelectionState {
	SELECT = 0,
	INVSELECT = 1,
	UNSELECT = 2, 
	DEFAULT = 0
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
private:
	std::vector<NoeudAbstrait*> selectionnes;
	SelectionState _state = SelectionState::SELECT;

	utilitaire::BoiteEnglobante _boundingBox;
	std::vector<glm::dvec3> _points; //Points formant le rectangle de sélection

	////////////////////////////////////////////////////////////////////////////////
	/// @func void SetNodeSelectedState(NoeudAbstrait* noeud, bool InsideSelection)
	/// @param[in] noeud Noeud ciblé
	/// @param[in] isInsideSelection Si le noeud fait parti de la sélection
	/// @return Nothing
	/// TODO: Trouver un meilleur nom
	/// Permet de changer l'état de sélection d'un noeud en fonction du scénario de sélection
	////////////////////////////////////////////////////////////////////////////////	
	void VisiteurSelection::setNodeSelectedState(NoeudAbstrait* noeud, bool isInsideSelection);


	////////////////////////////////////////////////////////////////////////////////
	/// @func std::vector<glm::dvec3> getPoints()
	/// @return Vecteur de l'ensemble des points formant la boîte de séleciton
	/// Permet d'obtenir les points formant le rectangle de sélection
	////////////////////////////////////////////////////////////////////////////////
	inline std::vector<glm::dvec3> getPoints();

	////////////////////////////////////////////////////////////////////////////////
	/// @func glm::dvec3 getPoint()
	/// @return Point à l'index donné
	/// Permet d'obtenir le point à l'index index. Si index est plus grand que la taille
	/// du vecteur, un wrapping est réalisé. Un index négatif retourne le n dernier élément
	////////////////////////////////////////////////////////////////////////////////
	glm::dvec3 getPoint(int index);

public:
	VisiteurSelection() {};
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
		setBoundingBox(utilitaire::BoiteEnglobante({ begin, end }));
	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn setBoundingBox
	///
	/// Permet de changer le bounding box pour la sélection
	///
	/// @param[in] utilitaire::BoiteEnglobante _box Boîte englobante représentant le rectangle élastique
	///
	/// @return Nothing
	///
	////////////////////////////////////////////////////////////////////////
	void setBoundingBox(utilitaire::BoiteEnglobante _box) {
		_boundingBox = _box;

		this->_points.clear();
		this->_points.push_back(glm::dvec3(this->_boundingBox.coinMin.x, this->_boundingBox.coinMin.y, 0));
		this->_points.push_back(glm::dvec3(this->_boundingBox.coinMin.x, this->_boundingBox.coinMax.y, 0));
		this->_points.push_back(glm::dvec3(this->_boundingBox.coinMax.x, this->_boundingBox.coinMax.y, 0));
		this->_points.push_back(glm::dvec3(this->_boundingBox.coinMax.x, this->_boundingBox.coinMin.y, 0));		
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


	glm::dvec3 getPosDataBinding() { return posDataBinding; }

	glm::dvec3 posDataBinding;



};

///////////////////////////////////////////////////////////////////////////
/// @class Selection
/// @brief Patron singleton de visiteur de la sélection
///
/// @author Carl-Vincent Landry-Duval
/// @date 2016-09-09
///////////////////////////////////////////////////////////////////////////
class SingletonSelection : private VisiteurSelection {
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
	/// @fn selectionner
	/// Permet d'obtenir les objets sélectionnés dans le carré donné
	/// @return Nothing
	////////////////////////////////////////////////////////////////////////
	void selectionner(
		glm::ivec2 begin, 
		glm::ivec2 end, 
		SelectionState state = SelectionState::SELECT);
};
#endif
