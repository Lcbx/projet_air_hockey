///////////////////////////////////////////////////////////////////////////////
/// @file AjoutPortail.h
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AjoutPortail.h"
#include "Souris.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"
#include "../../Commun/Utilitaire/Vue/Vue.h"



////////////////////////////////////////////////////////////////////////
///
/// @fn AjoutPortail::operationShortClick()
///
/// contient la logique d'ajout du portail (en fonction du premier et second click)
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void AjoutPortail::operationShortClick() {
	glm::dvec3 pointClick;  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), pointClick);
	//ajoute un portail dummy et le recupere (dernier enfant ajouté)
	FacadeModele::obtenirInstance()->ajouterPortail(X1(), Y1());
	auto dummy = (NoeudPortail*)FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants() - 1);
	//test le long du cercle
	bool garder = true;
	double rayon = dummy->obtenirRayon();
	int nbSegments = rayon;
	for (int i = 0; i < nbSegments; i++)
	{
		double theta = 2.0f * 3.1415926f * double(i) / double(nbSegments); //l'angle courant
		double cx = rayon * cosf(theta);
		double cy = rayon * sinf(theta);
		glm::vec3 point(pointClick.x + cx, pointClick.y + cy, 0);
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(point))
			garder = false;
	}
	//supprime le modele Dummy
	FacadeModele::obtenirInstance()->supprimerDernierObjet();
	//ajoute le vrai portail
	if (garder) if(clickInitial_) {
		FacadeModele::obtenirInstance()->ajouterPortail(X1(), Y1());
		clickInitial_ = false;
	}
	else {
		FacadeModele::obtenirInstance()->ajouterPortailDeux(X1(), Y1());
		clickInitial_ = true;
	}
}

void AjoutPortail::operationDragClick() {
	//DO something
}

////////////////////////////////////////////////////////////////////////
///
/// @fn AjoutPortail::escEnfonce()
///
/// permet d'annuler le premier Click
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void AjoutPortail::escEnfonce() {
	if(clickInitial_ == false)FacadeModele::obtenirInstance()->supprimerDernierObjet();
	clickInitial_ = true;
}