#include <iostream>
#include <string>

#include "VisiteurDuplication.h"
#include "VisiteurPointMilieu.h"
#include "ArbreRenduINF2990.h"




VisiteurDuplication::VisiteurDuplication() : visDep_(glm::vec3(0.f)) {}

void VisiteurDuplication::duplicate(glm::vec3 point) {
	VisiteurPointMilieu v(posCentre_);
	nosClones_ = v.getSelection();
	posActuelle_ = point;
	for (auto it = nosClones_.begin(); it != nosClones_.end() && (*it)->estSelectionne(); it++ )
		(*it)->accepter(this);
}

void VisiteurDuplication::actualise(glm::vec3 point) {
	for (auto it = nosClones_.begin(); it != nosClones_.end(); it++) {
		if (!(*it)->estSelectionne()) {
			(*it)->assignerSelection(true);
			visDep_.setDep(point - posActuelle_);
			visDep_.visiter(*it);
			(*it)->assignerSelection(false);
		}
	}
	posActuelle_ = point;
}

void VisiteurDuplication::finalise() {
	for (auto it = nosClones_.begin(); it != nosClones_.end();) {
		if (!(*it)->estSelectionne()) {
			it = nosClones_.erase(it);
		}
		else it++;
	}
}


void VisiteurDuplication::supprimerClones() {
	for (auto it = nosClones_.begin(); it != nosClones_.end(); ) {
		if (!(*it)->estSelectionne()) {
			(*it)->obtenirParent()->effacer(*it);
			it = nosClones_.erase(it);
		}
		else it++;
	}
}


void VisiteurDuplication::visiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne()) { 
	}
}

void VisiteurDuplication::visiter(NoeudComposite* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurDuplication::visiter(NoeudRondelle* noeud)
{
	if (noeud->estSelectionne()) {
	}
}

void VisiteurDuplication::visiter(NoeudMuret* noeud)
{
	if (noeud->estSelectionne()) {
		NoeudMuret* nouveau = new NoeudMuret(*noeud);
		nouveau->assignerSelection(false);
		nouveau->assignerPositionRelative(nouveau->obtenirPositionRelative() + posActuelle_ - posCentre_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveau);
		nosClones_.push_back((NoeudAbstrait*)nouveau);
	}
}

void VisiteurDuplication::visiter(NoeudBonus* noeud)
{
	if (noeud->estSelectionne()) {
		NoeudBonus* nouveau = new NoeudBonus(*noeud);
		nouveau->assignerSelection(false);
		nouveau->assignerPositionRelative(nouveau->obtenirPositionRelative() + posActuelle_ - posCentre_ );
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveau);
		nosClones_.push_back((NoeudAbstrait*)nouveau);
	}
}


void VisiteurDuplication::visiter(NoeudMaillet* noeud)
{
	if (noeud->estSelectionne()) {
	}
}

void VisiteurDuplication::visiter(NoeudPortail* noeud)
{
	if (noeud->estSelectionne() && noeud->getFrere()->estSelectionne()) {
		NoeudPortail* nouveau = new NoeudPortail(*noeud);
		nouveau->assignerSelection(false);
		nouveau->assignerPositionRelative(nouveau->obtenirPositionRelative() + posActuelle_ - posCentre_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveau);
		nosClones_.push_back((NoeudAbstrait*)nouveau);
	}
}