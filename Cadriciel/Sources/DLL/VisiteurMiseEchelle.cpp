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


VisiteurMiseEchelle::VisiteurMiseEchelle()
{
}

void VisiteurMiseEchelle::mettreEchelle(float facteur)
{
	facteur_ = facteur;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
	cout << "fn mettre echelle" << endl;

}


void VisiteurMiseEchelle::visiter(NoeudAbstrait* noeud)
{
	cout << "noeud bonus visiteur" << endl;
	float fact;

	fact = ((noeud->getScale()[0])) + facteur_ / 30;


	if (fact < 0.5)
	{
		fact = 0.5;
	}

	if (noeud->estSelectionne()) {

		noeud->setScale(glm::dvec3(fact, fact, 1.0));

	}


}

void VisiteurMiseEchelle::visiter(NoeudComposite* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurMiseEchelle::visiter(NoeudRondelle* noeud)
{


}

void VisiteurMiseEchelle::visiter(NoeudMuret* noeud)
{

}

void VisiteurMiseEchelle::visiter(NoeudBonus* noeud)
{
	cout << "noeud bonus visiteur" << endl;
	float fact;

	fact = ((noeud->getScale()[0])) + facteur_ / 30;


	if (fact < 0.5)
	{
		fact = 0.5;
	}

	if (noeud->estSelectionne()) {

		noeud->setScale(glm::dvec3(fact, fact, 1.0));

	}

}
void VisiteurMiseEchelle::visiter(NoeudMaillet* noeud)
{

}
void VisiteurMiseEchelle::visiter(NoeudPortail* noeud)
{

}