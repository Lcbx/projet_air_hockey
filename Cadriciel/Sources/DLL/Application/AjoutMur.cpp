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

void AjoutMur::start(int x, int y) {
	estEnfonce = false;
	if (clickInitial) { notrePosition_ = { x,y,x,y }; }
	else Souris::obtenirInstance()->getPosition() = { x,y,x,y };
}

void AjoutMur::current(int x, int y) {}

void AjoutMur::end(int x, int y) {
	notrePosition_[2] = x; notrePosition_[3] = y;
	(clickInitial ? plusDe3px(notrePosition_) : plusDe3px()) ? operationDragClick() : operationShortClick();
}

void AjoutMur::position(int x, int y) {
	glm::dvec3 pointClick;  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), pointClick);
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(pointClick)) {
		if (!clickInitial) {
			X2() = x; Y2() = y;
			FacadeModele::obtenirInstance()->ajouterMuretFantome(notrePosition_[0], notrePosition_[1], x, y);
			FacadeModele::obtenirInstance()->ajouterMuret(notrePosition_[0], notrePosition_[1], x, y);

		}
	}
}

void AjoutMur::operationShortClick() {
	glm::dvec3 pointClick;  FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(X1(), Y1(), pointClick);
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(pointClick)) {
		if (clickInitial) { clickInitial = false; estEnfonce == false;
		std::cout<<"premier: "<<estEnfonce<<std::endl;
		}
		else 
			if(estEnfonce == false){
			FacadeModele::obtenirInstance()->ajouterMuret(notrePosition_[0], notrePosition_[1], X2(), Y2());
			clickInitial = true;
			estEnfonce == false;
			std::cout << "deuxieme: " << estEnfonce << std::endl;

		}
	}
}

void AjoutMur::operationDragClick() {
	//DO something
}

void AjoutMur::escEnfonce() {
	estEnfonce = true;
	FacadeModele::obtenirInstance()->supprimerMuret(true);
	clickInitial = true;
}