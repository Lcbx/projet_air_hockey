///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDansLaTable.cpp
/// @author Luc Courbariaux
/// @date 2016-09-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurDansLaTable.h"
#include "ArbreRenduINF2990.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDansLaTable::VisiteurDansLaTable(glm::vec3 dep)
///
/// initialisation du visiteur verifiant si les noeuds sont dans la table
/// 
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////
VisiteurDansLaTable::VisiteurDansLaTable() {

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDansLaTable::visiter(NoeudAbstrait* noeud)
///
/// récupère les coordonnées du noeud en l'utilise pour calculer le point milieu
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDansLaTable::visiter(NoeudAbstrait* noeud)
{
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(noeud->obtenirPositionRelative()))
		result = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDansLaTable::visiter(NoeudComposite* noeud)
///
/// visite les noeuds inferieurs du composite
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDansLaTable::visiter(NoeudComposite* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurDansLaTable::visiter(NoeudRondelle* noeud)
{
	VisiteurDansLaTable::visiter((NoeudAbstrait*)noeud);
}

void VisiteurDansLaTable::visiter(NoeudMuret* noeud)
{
	VisiteurDansLaTable::visiter((NoeudAbstrait*)noeud);
}

void VisiteurDansLaTable::visiter(NoeudBonus* noeud)
{
	VisiteurDansLaTable::visiter((NoeudAbstrait*)noeud);
}

void VisiteurDansLaTable::visiter(NoeudMaillet* noeud)
{
	VisiteurDansLaTable::visiter((NoeudAbstrait*)noeud);
}

void VisiteurDansLaTable::visiter(NoeudPortail* noeud)
{
	VisiteurDansLaTable::visiter((NoeudAbstrait*)noeud);
}