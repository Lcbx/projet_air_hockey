#include <iostream>
#include <string>

#include "VisiteurDeplacement.h"
#include "ArbreRenduINF2990.h"


VisiteurDeplacement::VisiteurDeplacement(glm::vec3 dep) {
	dep_ = dep;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}


void VisiteurDeplacement::visiter(NoeudAbstrait* noeud)
{
	if(noeud->estSelectionne()) noeud->assignerPositionRelative(noeud->obtenirPositionRelative() + dep_);
}

void VisiteurDeplacement::visiter(NoeudComposite* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurDeplacement::visiter(NoeudRondelle* noeud)
{
	VisiteurDeplacement::visiter((NoeudAbstrait*)noeud);
}

void VisiteurDeplacement::visiter(NoeudMuret* noeud)
{
	VisiteurDeplacement::visiter((NoeudAbstrait*)noeud);
}

void VisiteurDeplacement::visiter(NoeudBonus* noeud)
{
	VisiteurDeplacement::visiter((NoeudAbstrait*)noeud);
}
void VisiteurDeplacement::visiter(NoeudMaillet* noeud)
{
	VisiteurDeplacement::visiter((NoeudAbstrait*)noeud);
}
void VisiteurDeplacement::visiter(NoeudPortail* noeud)
{
	VisiteurDeplacement::visiter((NoeudAbstrait*)noeud);
}