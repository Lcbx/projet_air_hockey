#include <iostream>
#include <string>

#include "VisiteurDeplacement.h"
#include "ArbreRenduINF2990.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::VisiteurDeplacement(glm::vec3 dep)
///
/// initialisation du visiteur de deplacement
/// 
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::VisiteurDeplacement(glm::vec3 dep) {
	dep_ = dep;
	tester_ = true;
	effectuer_ = true;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
	tester_ = false;
	if(effectuer_) FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::setDep(glm::vec3 dep)
///
/// retoumodifie la valeur du deplacement
/// 
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::setDep(glm::vec3 dep) {
	dep_ = dep;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::visiter(NoeudAbstrait* noeud)
///
/// verifie qu'on peut faire le déplacement, puis l'effectue
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne()) {
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(noeud->obtenirPositionRelative() + dep_))
			effectuer_ = false;
		else if (!tester_ && effectuer_)
			noeud->assignerPositionRelative(noeud->obtenirPositionRelative() + dep_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::visiter(NoeudComposite* noeud)
///
/// visite les noeuds inferieur du composite
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
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