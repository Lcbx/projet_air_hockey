///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.cpp
/// @author Wajdi Gharsalli
/// @date 2016-09-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

#include "VisiteurDeplacement.h"


VisiteurDeplacement::VisiteurDeplacement(glm::dvec3 posIni, glm::dvec3 posFin)
{
	posIni_ = posIni;
	posFin_ = posFin;
}



void VisiteurDeplacement::visiter(NoeudAbstrait* noeud)
{

}

void VisiteurDeplacement::visiter(NoeudComposite* noeud)
{



}

void VisiteurDeplacement::visiter(NoeudRondelle* noeud)
{


}

void VisiteurDeplacement::visiter(NoeudMuret* noeud)
{

}

void VisiteurDeplacement::visiter(NoeudBonus* noeud)
{
	glm::dvec3 Diff;
	Diff.x = posFin_.x - posIni_.x;
	Diff.y = posFin_.y - posIni_.y;
	
	glm::dvec3 nvPos;

	if (noeud->estSelectionne())
	{
		nvPos.x = noeud->obtenirPositionRelative().x + Diff.x;
		nvPos.y= noeud->obtenirPositionRelative().y + Diff.y;
	
		noeud->assignerPositionRelative(nvPos);//changer la postion de l'objet
	}

}



void VisiteurDeplacement::visiter(NoeudMaillet* noeud)
{

}
void VisiteurDeplacement::visiter(NoeudPortail* noeud)
{

}