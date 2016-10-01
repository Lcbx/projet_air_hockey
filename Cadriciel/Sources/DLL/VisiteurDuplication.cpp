#include <iostream>
#include <string>

#include "VisiteurDuplication.h"
#include "VisiteurPointMilieu.h"
#include "ArbreRenduINF2990.h"
#include "../Vue/Vue.h"
#include "FacadeModele.h"




VisiteurDuplication::VisiteurDuplication() : visDep_(glm::vec3(0.f)) {
	VisiteurPointMilieu v( posCentre_ );
	selection_ = v.getSelection();
}

void VisiteurDuplication::duplicate(glm::vec3 point) {
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle((int)point.x, (int)point.y, (glm::dvec3) posActuelle_);
	for (auto it = selection_.begin(); it != selection_.end(); it++) {
		(*it)->accepter(this);
	}
}

void VisiteurDuplication::actualiser(glm::vec3 point) {
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle((int)point.x, (int)point.y, (glm::dvec3) point);
	for (auto it = selection_.begin(); it != selection_.end(); it++) {
		visDep_.setDep( (*it)->obtenirPositionRelative() + point - posActuelle_);
		visDep_.visiter(*it);
	}
	posActuelle_ = point;
}

void VisiteurDuplication::supprimerClones() {
	while (!selection_.empty()) selection_.front()->obtenirParent()->effacer(selection_.front());
}

void VisiteurDuplication::creerClones() {
	
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
		selection_.push_back( (NoeudAbstrait*)nouveauBonus );
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