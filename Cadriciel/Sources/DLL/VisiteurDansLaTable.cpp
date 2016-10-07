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
	cout << "DansLaTable : " << (result_ ? "true\n" : "false\n");
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
/// verifie le long du noeud muret
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void VisiteurDansLaTable::visiter(NoeudMuret* noeud)
{
	//test le long du mur s'il est dans la table
	glm::dvec3 debut = noeud->obtenirDroiteDirectrice().lirePoint();
	glm::dvec3 fin = debut + noeud->obtenirDroiteDirectrice().lireVecteur();
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
	//test le long du segment s'il est dans la table
	glm::dvec3 debut = noeud->obtenirDroiteDirectrice().lirePoint();
	glm::dvec3 fin = debut + noeud->obtenirDroiteDirectrice().lireVecteur();
	//double rayon = noeud->obtenirRayonModele();
	//glm::dvec3 pos = noeud->obtenirPositionRelative();
	//glm::dvec3 dir = rayon*noeud->obtenirDroiteDirectrice().lireVecteur()/ glm::length(noeud->obtenirDroiteDirectrice().lireVecteur());
	//glm::dvec3 debut(pos - dir);
	//glm::dvec3 fin(pos + dir);
	//tout les 2 pixels
	double length = 0.5 * glm::distance(debut, fin);
	glm::dvec3 vec = (fin - debut) / length;
	for (int i = 1; i < length; i++) {
		debut += vec;
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(debut))
			result_ = false;
	}
}

void VisiteurDansLaTable::visiter(NoeudMaillet* noeud)
{
}

void VisiteurDansLaTable::visiter(NoeudPortail* noeud)
{
	//test le long du cercle
	bool garder = true;
	auto centre = noeud->obtenirPositionRelative();
	double rayon = noeud->obtenirRayon();
	int nbSegments = rayon;
	for (int i = 0; i < nbSegments; i++)
	{
		double theta = 2.0f * 3.1415926f * double(i) / double(nbSegments); //l'angle courant
		double cx = rayon * cosf(theta);
		double cy = rayon * sinf(theta);
		glm::vec3 point(centre.x + cx, centre.y + cy, 0);
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(point))
			result_ = false;
	}
}