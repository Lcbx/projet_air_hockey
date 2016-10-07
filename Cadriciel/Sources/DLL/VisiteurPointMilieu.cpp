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


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurPointMilieu::VisiteurPointMilieu(glm::vec3 dep)
///
/// initialisation du visiteur de point milieu
/// 
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////
VisiteurPointMilieu::VisiteurPointMilieu(glm::vec3& pointARendre) : posCentre_(pointARendre) {
	nbrNoeudsVisites_ = 0;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurPointMilieu::visiter(NoeudAbstrait* noeud)
///
/// récupère les coordonnées du noeu en l'utilise pour calculer le point milieu
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurPointMilieu::getSelection()
///
/// retourne tous les noeuds selctionnés
/// 
/// @return std::list<NoeudAbstrait*> 
///
/////////////////////////////////////////////////////////////////////////
std::list<NoeudAbstrait*> VisiteurPointMilieu::getSelection() {
	return selection_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurPointMilieu::visiter(NoeudComposite* noeud)
///
/// visite les noeuds inferieurs du composite
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
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