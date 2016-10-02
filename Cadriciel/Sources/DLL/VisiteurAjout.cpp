///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAjout.cpp
/// @author Wajdi Gharsalli
/// @date 2016-09-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include"FacadeModele.h"
#include "VisiteurAjout.h"
#include "ArbreRenduINF2990.h"



VisiteurAjout::VisiteurAjout(glm::dvec3 pos)
{
	position = pos;

}

void VisiteurAjout::visiter(NoeudAbstrait* noeud)

{

}

void VisiteurAjout::visiter(NoeudComposite* noeud)
{



}
void VisiteurAjout::visiter(NoeudRondelle* noeud) 
{


}

void VisiteurAjout::visiter(NoeudMuret* noeud) 
{
	noeud->assignerPositionRelative(position);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);
}

void VisiteurAjout::visiter(NoeudBonus* noeud)
{
	noeud->assignerPositionRelative(position);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);
}
void VisiteurAjout::visiter(NoeudMaillet* noeud)
{

}
void VisiteurAjout::visiter(NoeudPortail* noeud)
{
	noeud->assignerPositionRelative(position);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);
}
