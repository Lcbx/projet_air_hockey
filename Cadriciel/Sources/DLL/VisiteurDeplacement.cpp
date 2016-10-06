///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.cpp
/// @author Luc Courbariaux
/// @date 2016-09-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurDeplacement.h"
#include "ArbreRenduINF2990.h"
#include "VisiteurDansLaTable.h"

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
	effectuer_ = true;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
	//verifie si le deplacement est legit
	VisiteurDansLaTable v(effectuer_);
	if(!effectuer_) FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::setDep(glm::vec3 dep)
///
/// modifie la valeur du deplacement
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
		if (effectuer_) //deplace le noeud
			noeud->assignerPositionRelative(noeud->obtenirPositionRelative() + dep_);
		else //le remet a sa place
			noeud->assignerPositionRelative(noeud->obtenirPositionRelative() - dep_);
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