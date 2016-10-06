///////////////////////////////////////////////////////////////////////////////
/// @file AjoutMur.cpp
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AjoutMur.h"
#include "Souris.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"
#include "../../Commun/Utilitaire/Vue/Vue.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn AjoutMur::start(int x, int y)
///
/// permet d'initialiser les deux clicks nécessaire a l'ajout d'un mur
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void AjoutMur::start(int x, int y) {
	if (clickInitial) {
		notrePosition_ = { x,y,x,y };
	}
	else {
		Souris::obtenirInstance()->getPosition() = { x,y,x,y };
	}
}

void AjoutMur::current(int x, int y) {}

////////////////////////////////////////////////////////////////////////
///
/// @fn AjoutMur::end(int x, int y)
///
/// permet de finir les deux clicks nécessaire a l'ajout d'un mur
/// en vérifiant qu'il s'agit bien de deux clicks simples
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void AjoutMur::end(int x, int y) {
	notrePosition_[2] = x; notrePosition_[3] = y;
	(clickInitial ? plusDe3px(notrePosition_) : plusDe3px()) ? operationDragClick() : operationShortClick();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn AjoutMur::position(int x, int y)
///
/// affiche le mur fantome entre l'emplacement du premier click
/// et la postion de la souris
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void AjoutMur::position(int x, int y) {
	glm::dvec3 pointClick;  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), pointClick);
	if (!clickInitial && FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(pointClick)) {
		X2() = x; Y2() = y;
		FacadeModele::obtenirInstance()->supprimerMuret(true);
		FacadeModele::obtenirInstance()->ajouterMuret(notrePosition_[0], notrePosition_[1], x, y);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn AjoutMur::operationShortClick()
///
/// contient la logique d'ajout du mur (en fonction du premier et second click)
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void AjoutMur::operationShortClick() {
	glm::dvec3 pointClick;  
	if(!clickInitial)
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), pointClick);
	else
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(notrePosition_.x, notrePosition_.y, pointClick);

	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(pointClick)) {
		if (clickInitial) { clickInitial = false; }
		else {
			FacadeModele::obtenirInstance()->supprimerMuret(true);
			//test le long du mur s'il est dans la table
			bool ajouter = true;
			glm::dvec3 debut; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(notrePosition_[0], notrePosition_[1], debut);
			glm::dvec3 fin; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), fin);
			//tout les 2 pixels
			double length = 0.5 * glm::distance(debut, fin);
			glm::dvec3 vec = (fin - debut) / length;
			for (int i = 1; i < length; i++) {
				debut += vec;
				if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(debut)) 					
					ajouter = false;
			}
			if (ajouter) {
				FacadeModele::obtenirInstance()->ajouterMuret(notrePosition_[0], notrePosition_[1], X2(), Y2());
				FacadeModele::obtenirInstance()->ajouterMuret(notrePosition_[0], notrePosition_[1], X2(), Y2());
			}
			else FacadeModele::obtenirInstance()->supprimerMuret(true);
			clickInitial = true;
		}
	}
}

void AjoutMur::operationDragClick() {
	//DO something
}

////////////////////////////////////////////////////////////////////////
///
/// @fn AjoutMur::escEnfonce()
///
/// permet d'annuler le premier Click
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void AjoutMur::escEnfonce() {
	FacadeModele::obtenirInstance()->supprimerMuret(true);
	clickInitial = true;
}