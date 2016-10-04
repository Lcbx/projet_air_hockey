///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurPointMilieu.cpp
/// @author Luc Courbariaux
/// @date 2016-09-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurPointMilieu.h"
#include "ArbreRenduINF2990.h"

VisiteurPointMilieu::VisiteurPointMilieu(glm::vec3& pointARendre) : posCentre_(pointARendre) {
	nbrNoeudsVisites_ = 0;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}


void VisiteurPointMilieu::visiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne()) {
		selection_.push_back(noeud);
		auto posNoeud = noeud->obtenirPositionRelative();
		posCentre_ *= nbrNoeudsVisites_++;
		posCentre_ += posNoeud;
		posCentre_ /= (float)nbrNoeudsVisites_;
	}
}

std::list<NoeudAbstrait*> VisiteurPointMilieu::getSelection() {
	return selection_;
}

void VisiteurPointMilieu::visiter(NoeudComposite* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurPointMilieu::visiter(NoeudRondelle* noeud)
{
	VisiteurPointMilieu::visiter((NoeudAbstrait*)noeud);
}

void VisiteurPointMilieu::visiter(NoeudMuret* noeud)
{
	VisiteurPointMilieu::visiter((NoeudAbstrait*)noeud);
}

void VisiteurPointMilieu::visiter(NoeudBonus* noeud)
{
	VisiteurPointMilieu::visiter((NoeudAbstrait*)noeud);
}


void VisiteurPointMilieu::visiter(NoeudMaillet* noeud)
{
	VisiteurPointMilieu::visiter((NoeudAbstrait*)noeud);
}

void VisiteurPointMilieu::visiter(NoeudPortail* noeud)
{
	VisiteurPointMilieu::visiter((NoeudAbstrait*)noeud);
}