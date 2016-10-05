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
/// @fn VisiteurDansLaTable::VisiteurDansLaTable(bool& result)
///
/// initialisation du visiteur verifiant si les noeuds sont dans la table
/// met le resultat dans le booleen passé en argument 
///
/// @return Aucune (constructeur).
///
/////////////////////////////////////////////////////////////////////////
VisiteurDansLaTable::VisiteurDansLaTable(bool& result) : result_(result) {
	result_ = true;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
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
	if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(noeud->obtenirPositionRelative()))
		result_ = false;
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

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDansLaTable::visiter(NoeudMuret* noeud)
///
/// verifie le long de sa trajectoire du noeud muret
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDansLaTable::visiter(NoeudMuret* noeud)
{
	//test le long du mur s'il est dans la table
	glm::dvec3 debut = noeud->obtenirDroiteDirectrice().lirePoint();
	glm::dvec3 fin = debut + noeud->obtenirDroiteDirectrice().lireVecteur() ;
	//tout les 2 pixels
	double length = 0.5 * glm::distance(debut, fin);
	glm::dvec3 vec = (fin - debut) / length;
	for (int i = 1; i < length; i++) {
		debut += vec;
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(debut))
			result_ = false;
	}
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