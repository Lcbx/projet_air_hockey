#include <iostream>
#include <string>

#include "VisiteurDuplication.h"
#include "VisiteurPointMilieu.h"
#include "ArbreRenduINF2990.h"
#include "../Vue/Vue.h"
#include "FacadeModele.h"




VisiteurDuplication::VisiteurDuplication() : visDep_(glm::vec3(0.f)) {
	VisiteurPointMilieu v( posCentre_ );
	nosClones_ = v.getSelection();
}

void VisiteurDuplication::duplicate(glm::vec3 point) {
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle((int)point.x, (int)point.y, (glm::dvec3) posActuelle_);
	for (auto it = nosClones_.begin(); it != nosClones_.end() || !(*it)->estSelectionne(); nosClones_.pop_back()) {
		(*it)->accepter(this);
	}
}

void VisiteurDuplication::actualise(glm::vec3 point) {
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle((int)point.x, (int)point.y, (glm::dvec3) point);
	for (auto it = nosClones_.begin(); it != nosClones_.end(); it++) {
		(*it)->assignerSelection(true);
		visDep_.setDep( (*it)->obtenirPositionRelative() + point - posActuelle_);
		visDep_.visiter(*it);
		(*it)->assignerSelection(false);
	}
	posActuelle_ = point;
}

void VisiteurDuplication::supprimerClones() {
	while (!nosClones_.empty()) nosClones_.front()->obtenirParent()->effacer(nosClones_.front());
}

void VisiteurDuplication::escEnfonce() {
	supprimerClones();
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
	}
}

void VisiteurDuplication::visiter(NoeudBonus* noeud)
{
	if (noeud->estSelectionne()) {
		NoeudBonus* nouveauBonus = new NoeudBonus(*noeud);
		nouveauBonus->assignerSelection(false);
		nouveauBonus->assignerPositionRelative(  nouveauBonus->obtenirPositionRelative() + posActuelle_ - posCentre_ );
		nosClones_.push_back( (NoeudAbstrait*)nouveauBonus );
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveauBonus);
	}
}


void VisiteurDuplication::visiter(NoeudMaillet* noeud)
{
	if (noeud->estSelectionne()) {
	}
}

void VisiteurDuplication::visiter(NoeudPortail* noeud)
{
	if (noeud->estSelectionne()) {
	}
}