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


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAjout::VisiteurAjout(glm::dvec3 pos)
///
/// Constructeur par parametres
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
VisiteurAjout::VisiteurAjout(glm::dvec3 pos)
{
	position = pos;

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
void VisiteurAjout::visiter(NoeudAbstrait* noeud)

{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudComposite* noeud)
///
/// rien
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAjout::visiter(NoeudComposite* noeud)
{



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
void VisiteurAjout::visiter(NoeudRondelle* noeud) 
{


}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudMuret* noeud)
///
/// Ajouter le muret
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAjout::visiter(NoeudMuret* noeud) 
{
	noeud->assignerPositionRelative(position);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudBonus* noeud)
///
/// Ajouter Noeud bonus
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAjout::visiter(NoeudBonus* noeud)
{
	noeud->assignerPositionRelative(position);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);
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
void VisiteurAjout::visiter(NoeudMaillet* noeud)
{
	noeud->assignerPositionRelative(position);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurMiseEchelle::visiter(NoeudPortail* noeud)
///
/// ajouter un portail
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAjout::visiter(NoeudPortail* noeud)
{
	noeud->assignerPositionRelative(position);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud);
}
