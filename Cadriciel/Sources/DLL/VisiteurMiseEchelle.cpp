///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseEchelle.cpp
/// @author Wajdi Gharsalli
/// @date 2016-09-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

#include "VisiteurMiseEchelle.h"
#include "ArbreRenduINF2990.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseEchelle::VisiteurMiseEchelle()
///
/// Constructeur par defaut
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
VisiteurMiseEchelle::VisiteurMiseEchelle()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::mettreEchelle(float facteur)
///
/// appliquer le facteur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseEchelle::mettreEchelle(float facteur)
{
	facteur_ = facteur;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudAbstrait* noeud)
///
/// rien
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseEchelle::visiter(NoeudAbstrait* noeud)
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudComposite* noeud)
///
/// Parcourir l'arbre
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseEchelle::visiter(NoeudComposite* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudRondelle* noeud)
///
/// rien
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseEchelle::visiter(NoeudRondelle* noeud)
{


}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudMuret* noeud)
///
/// Appliquer le mise a echelle pour le muret
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseEchelle::visiter(NoeudMuret* noeud)
{
	float fact= 0;
	fact = ((noeud->getScale()[0])) + facteur_/5;


	if (fact < 0.5)
	{
		fact = 0.5;
	}
	if (fact > 14)
	{
		fact = 14;
	}

	if (noeud->estSelectionne()) {

		noeud->setScale(glm::dvec3(fact, noeud->getScale().y, 1));

	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudBonus* noeud)
///
/// appliquer mise a echelle pour le bonus
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseEchelle::visiter(NoeudBonus* noeud)
{
	float fact=0;

	fact = ((noeud->getScale()[0])) + facteur_ / 30;

	//valeurs limites pour agrandir ou reduire un objet
	if (fact < 0.5)
	{
		fact = 0.5;
	}
	if (fact > 6)
	{
		fact = 6;
	}

	if (noeud->estSelectionne()) {

		noeud->setScale(glm::dvec3(fact, fact, 1.0));
	}

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudMaillet* noeud)
///
/// rien
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseEchelle::visiter(NoeudMaillet* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudPortail* noeud)
///
/// Appliquer la mise a echelle pour le portail
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseEchelle::visiter(NoeudPortail* noeud)
{
	float fact=0;

	fact = ((noeud->getScale()[0])) + facteur_ / 30;
	
	//valeurs limites pour mise a echelle
	if (fact > 6)
	{
		fact = 6;
	}

	if (fact < 0.5)
	{
		fact = 0.5;
	}

	if (noeud->estSelectionne()) {

		noeud->setScale(glm::dvec3(fact, fact, 1.0));

	}
}