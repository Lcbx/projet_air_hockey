#include <iostream>
#include <string>

#include "VisiteurDuplication.h"
#include "VisiteurPointMilieu.h"
#include "ArbreRenduINF2990.h"
#include "../Vue/Vue.h"
#include "FacadeModele.h"

void VisiteurDuplication::fantomDuplicate(glm::vec3 point) {
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle( (int)point.x, (int)point.y, (glm::dvec3) point);
}

void VisiteurDuplication::finalDuplicate(glm::vec3 point) {
	
}


void VisiteurDuplication::visiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne()) {}
}

void VisiteurDuplication::visiter(NoeudComposite* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurDuplication::visiter(NoeudRondelle* noeud)
{
	VisiteurDuplication::visiter((NoeudAbstrait*)noeud);
}

void VisiteurDuplication::visiter(NoeudMuret* noeud)
{
	VisiteurDuplication::visiter((NoeudAbstrait*)noeud);
}

void VisiteurDuplication::visiter(NoeudBonus* noeud)
{
	VisiteurDuplication::visiter((NoeudAbstrait*)noeud);
}


void VisiteurDuplication::visiter(NoeudMaillet* noeud)
{
	VisiteurDuplication::visiter((NoeudAbstrait*)noeud);
}

void VisiteurDuplication::visiter(NoeudPortail* noeud)
{
	VisiteurDuplication::visiter((NoeudAbstrait*)noeud);
}