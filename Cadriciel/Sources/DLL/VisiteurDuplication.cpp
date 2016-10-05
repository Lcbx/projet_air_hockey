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
	tester_ = true;
	effectuer_ = true;
	for (auto it = nosClones_.begin(); it != nosClones_.end() && (*it)->estSelectionne(); it++)
		(*it)->accepter(this);
	tester_ = false;
	if (effectuer_)
		for (auto it = nosClones_.begin(); it != nosClones_.end() && (*it)->estSelectionne(); it++)
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
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(noeud->obtenirPositionRelative() + posActuelle_ - posCentre_))
			effectuer_ = false;
		else if (!tester_ && effectuer_) {
			NoeudMuret* nouveau = new NoeudMuret(*noeud);
			nouveau->assignerSelection(false);
			nouveau->assignerPositionRelative(nouveau->obtenirPositionRelative() + posActuelle_ - posCentre_);
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveau);
			nosClones_.push_back((NoeudAbstrait*)nouveau);
		}
	}
}

void VisiteurDuplication::visiter(NoeudBonus* noeud)
{
	if (noeud->estSelectionne()) {
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(noeud->obtenirPositionRelative() + posActuelle_ - posCentre_))
			effectuer_ = false;
		else if (!tester_ && effectuer_) {
			NoeudBonus* nouveau = new NoeudBonus(*noeud);
			nouveau->assignerSelection(false);
			nouveau->assignerPositionRelative(nouveau->obtenirPositionRelative() + posActuelle_ - posCentre_);
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveau);
			nosClones_.push_back((NoeudAbstrait*)nouveau);
		}
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
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(noeud->obtenirPositionRelative() + posActuelle_ - posCentre_)
			&& !FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(noeud->getFrere()->obtenirPositionRelative() + posActuelle_ - posCentre_))
			effectuer_ = false;
		else if (!tester_ && effectuer_) {
			//evite de faire des doubles supplementaires
			auto frere = std::find(nosClones_.begin(), nosClones_.end(), noeud->getFrere());
			nosClones_.erase(frere);
			nosClones_.push_front(noeud->getFrere());
			//on crait les noeuds freres en meme temps
			NoeudPortail* nouveau1 = new NoeudPortail(*noeud);
			NoeudPortail* nouveau2 = new NoeudPortail(*((NoeudPortail*)noeud->getFrere()));
			//assigner les nouveaux freres entre eux
			nouveau1->setFrere(nouveau2);
			nouveau2->setFrere(nouveau1);
			//les deselectionner
			nouveau1->assignerSelection(false);
			nouveau2->assignerSelection(false);
			//les placer
			nouveau1->assignerPositionRelative(nouveau1->obtenirPositionRelative() + posActuelle_ - posCentre_);
			nouveau2->assignerPositionRelative(nouveau2->obtenirPositionRelative() + posActuelle_ - posCentre_);
			//les ajouter
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveau1);
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveau2);
			//les ajouter a notre liste
			nosClones_.push_back((NoeudAbstrait*)nouveau1);
			nosClones_.push_back((NoeudAbstrait*)nouveau2);
		}
	}
}