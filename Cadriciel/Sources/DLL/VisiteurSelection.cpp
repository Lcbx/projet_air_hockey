///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.cpp
/// @author Wajdi Gharsalli
/// @date 2016-09-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
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
	} else {
		switch (_state) {
		case SelectionState::SELECT:
			noeud->assignerSelection(false);
			break;
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
	math::Droite3D droiteDirectrice = noeud->obtenirDroiteDirectrice();
	double rayon = noeud->obtenirRayon();

	double minDist = INFINITY;
	size_t pointsSize = this->getPoints().size();

	//Si un point est sur la droite et dans la droite du muret, 
	double l = glm::length(droiteDirectrice.lireVecteur()); // Longeur de la droite
	for (size_t i = 0; i < pointsSize; i++) {
		double a = glm::distance(droiteDirectrice.lirePoint(), this->getPoint(i)); // Longeur point A et autre point
		double b = glm::distance(droiteDirectrice.lirePoint() + droiteDirectrice.lireVecteur(), this->getPoint(i)); // Longeur point B et autre point
		if (a <= l && b <= l) {	//On reste dans la droite si a <= l et b <= l
			minDist = min(minDist, droiteDirectrice.distancePoint(this->getPoint(i)));
		}
	}
	
	/// Click near or inside
	if (rayon >= minDist) {
		this->setNodeSelectedState(noeud, true);
	} /// Object inside selection
	else if (PointInsideBoundingBox(this->_boundingBox, noeud->obtenirPositionRelative())) {
		this->setNodeSelectedState(noeud, true);
	} /// Le rectangle coïncide avec la droite (collision)
	else {
		bool doesCollides = false;
		for (int i = 0; i < pointsSize; i++) { //Est-ce que les deux droites s'intersectent
			doesCollides |= droiteDirectrice.intersectionSegment(this->getPoint(i), this->getPoint(i + 1));
		}

		this->setNodeSelectedState(noeud, doesCollides);
	}
}

void VisiteurSelection::visiter(NoeudBonus* noeud) {
	math::Droite3D droiteDirectrice = noeud->obtenirDroiteDirectrice();
	double rayon = noeud->obtenirRayon();

	double minDist = INFINITY;
	size_t pointsSize = this->getPoints().size();

	//Si un point est sur la droite et dans la droite du muret, 
	double l = glm::length(droiteDirectrice.lireVecteur()); // Longeur de la droite
	for (size_t i = 0; i < pointsSize; i++) {
		double a = glm::distance(droiteDirectrice.lirePoint(), this->getPoint(i)); // Longeur point A et autre point
		double b = glm::distance(droiteDirectrice.lirePoint() + droiteDirectrice.lireVecteur(), this->getPoint(i)); // Longeur point B et autre point
		if (a <= l && b <= l) {	//On reste dans la droite si a <= l et b <= l
			minDist = min(minDist, droiteDirectrice.distancePoint(this->getPoint(i)));
		}
	}

	/// Click near or inside
	if (rayon >= minDist) {
		this->setNodeSelectedState(noeud, true);
	} /// Object inside selection
	else if (PointInsideBoundingBox(this->_boundingBox, noeud->obtenirPositionRelative())) {
		this->setNodeSelectedState(noeud, true);
	} /// Le rectangle coïncide avec la droite (collision)
	else {
		bool doesCollides = false;
		for (int i = 0; i < pointsSize; i++) { //Est-ce que les deux droites s'intersectent
			doesCollides |= droiteDirectrice.intersectionSegment(this->getPoint(i), this->getPoint(i + 1));
		}

		this->setNodeSelectedState(noeud, doesCollides);
	}
}

void VisiteurSelection::visiter(NoeudMaillet* noeud) { }

void VisiteurSelection::visiter(NoeudPortail* noeud) {
	double rayon = noeud->obtenirRayon();

	double minDist = INFINITY;
	int pointsSize = this->getPoints().size();

	// TODO: Take into account transformations
	glm::dvec3 centre = noeud->obtenirPositionRelative();
	//centre = centre + glm::dvec3{ 10,0,0 };

	// Distance minimale du point
	for (int i = 0; i < pointsSize; i++) {
		double a = glm::distance(centre, this->getPoint(i));
		minDist = min(minDist, a);
	}

	if (rayon >= minDist) {
		this->setNodeSelectedState(noeud, true);
	} else if (PointInsideBoundingBox(this->_boundingBox, centre)) {
		this->setNodeSelectedState(noeud, true);
	} else {
		/// Calcul de collision entre le portail et la boîte de sélection
		bool collides = false;
		for (int i = 0; i < pointsSize; i++) {
			aidecollision::Collision status = 
				aidecollision::calculerCollisionSegment(this->getPoint(i), this->getPoint(i + 1), centre, rayon)
				.type;
			collides |= status != aidecollision::Collision::COLLISION_AUCUNE;
		}

		this->setNodeSelectedState(noeud, collides);
	}
}

//TODO: Refactoriser
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

///Permet d'obtenir les points formant le rectangle
inline std::vector<glm::dvec3> VisiteurSelection::getPoints() {
	return this->_points;
}

///Permet d'obtenir le point à l'index donné avec wrapping (-1 = dernier item, n+1 = premier item)
glm::dvec3 VisiteurSelection::getPoint(int index) {
	size_t index_ = index;
	return this->getPoint(index_);
}


///Permet d'obtenir le point à l'index donné avec wrapping (-1 = dernier item, n+1 = premier item)
glm::dvec3 VisiteurSelection::getPoint(size_t index) {
	std::vector<glm::dvec3> vec = this->getPoints();
	if (index % vec.size() >= 0) {
		return vec[index % vec.size()];
	}
	else {
		return vec[vec.size() - (index % vec.size())];
	}
}
