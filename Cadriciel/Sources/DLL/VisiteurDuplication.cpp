///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.cpp
/// @author Luc Courbariaux
/// @date 2016-10-05
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "VisiteurDuplication.h"
#include "VisiteurPointMilieu.h"
#include "VisiteurDansLaTable.h"
#include "ArbreRenduINF2990.h"



////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::VisiteurDuplication()
///
/// initialisation du visiteur de duplication
/// determine le centre de la selection
///
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication() : visDep_(glm::vec3(0.f)) {}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::duplicate(glm::vec3 point)
///
/// determine s'il est possible de dupliquer, crait les clones et les place
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::duplicate(glm::vec3 point) {
	VisiteurPointMilieu v(posCentre_);
	originaux_ = v.getSelection();
	posActuelle_ = point;
	for (auto it = originaux_.begin(); it != originaux_.end(); it++)
		(*it)->accepter(this);
	VisiteurDansLaTable t(effectuer_);
	if (!effectuer_) supprimerClones();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::actualise(glm::vec3 point)
///
/// deplace les clones selon la souris
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::actualise(glm::vec3 point) {
	for (auto it = nosClones_.begin(); it != nosClones_.end(); it++)
		(*it)->assignerSelection(true);
	for (auto it = originaux_.begin(); it != originaux_.end(); it++)
		(*it)->assignerSelection(false);
	visDep_ = VisiteurDeplacement(point - posActuelle_);
	for (auto it = nosClones_.begin(); it != nosClones_.end(); it++)
		(*it)->assignerSelection(false);
	for (auto it = originaux_.begin(); it != originaux_.end(); it++)
		(*it)->assignerSelection(true);
	if(visDep_.reussi()) posActuelle_ = point;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::finalise()
///
/// termine la duplication
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::finalise() {
	for (auto it = nosClones_.begin(); it != nosClones_.end();) {
		it = nosClones_.erase(it);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::supprimerClones()
///
/// supprime les clones
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::supprimerClones() {
	for (auto it = nosClones_.begin(); it != nosClones_.end(); ) {
		(*it)->obtenirParent()->effacer(*it);
		it = nosClones_.erase(it);
	}
}


void VisiteurDuplication::visiter(NoeudAbstrait* noeud)
{}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudComposite* noeud)
///
/// visite les noeuds inferieur du composite
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudComposite* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurDuplication::visiter(NoeudRondelle* noeud)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudMuret* noeud)
///
/// crait le clone
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudMuret* noeud)
{

	NoeudMuret* nouveau = new NoeudMuret(*noeud);
	nouveau->assignerSelection(false);
	nouveau->assignerPositionRelative(nouveau->obtenirPositionRelative() + posActuelle_ - posCentre_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveau);
	nosClones_.push_back((NoeudAbstrait*)nouveau);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudBonus* noeud)
///
/// crait le clone
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudBonus* noeud)
{
	NoeudBonus* nouveau = new NoeudBonus(*noeud);
	nouveau->assignerSelection(false);
	nouveau->assignerPositionRelative(nouveau->obtenirPositionRelative() + posActuelle_ - posCentre_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter((NoeudAbstrait*)nouveau);
	nosClones_.push_back((NoeudAbstrait*)nouveau);
}


void VisiteurDuplication::visiter(NoeudMaillet* noeud)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudPortail* noeud)
///
/// verifie que le frere est selectiionne, crait les clones
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudPortail* noeud)
{
	if (noeud->estSelectionne() && noeud->getFrere()->estSelectionne()) {
		//evite de faire des doubles supplementaires
		auto frere = std::find(originaux_.begin(), originaux_.end(), noeud->getFrere());
		originaux_.erase(frere);
		originaux_.push_front(noeud->getFrere());
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