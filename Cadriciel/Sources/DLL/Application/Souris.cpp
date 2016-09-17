///////////////////////////////////////////////////////////////////////////////
/// @file Souris.cpp
/// @author Luc Courbariaux
/// @date 2016-09-12
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


#include "Souris.h"
#include <AideGL.h>
#include <FacadeModele.h>

#include "glm\glm.hpp"

using namespace aidegl;



Souris* Souris::instance_{ nullptr };

Souris::Souris() {
	creerStrategie();
};

Souris* Souris::obtenirInstance() {
	if (instance_ == nullptr) instance_ = new Souris;
	return instance_;
}

void Souris::libererInstance() {
	delete notreStrategie_;
	delete instance_;
	instance_ = nullptr;
	notreStrategie_ = nullptr;
}

void Souris::EtatdelaSouris(int etat) {
	etatSouris = static_cast<Etats>(etat);
	if (notreStrategie_ != nullptr) delete notreStrategie_;
	creerStrategie();
}

void Souris::creerStrategie(){
	switch (etatSouris) {
	case SELECTION: { notreStrategie_ = new Selection;  break; }
	case LOUPE: { break; }
	case DEPLACEMENT: { break; }
	case ROTATION: { break; }
	case DUPLICATION: { break; }
	case AJOUT_ACCELERATEUR: {}
	case DEBUT_AJOUT_MUR: { break; }
	case AJOUT_MUR: { break; }
	case DEBUT_AJOUT_PORTAIL: { break; }
	case AJOUT_PORTAIL: { break; }
	default: {
		notreStrategie_ = nullptr;
	}
	}
}

void Souris::toucheControl(bool pressee) {
	toucheControlPressee = pressee;
}

void Souris::startClick(int x, int y) {
	notreStrategie_->start(x, y);
}

void Souris::currentClick(int x, int y) {
	notreStrategie_->current( x, y);
}

void Souris::endClick(int x, int y) {
	notreStrategie_->end(x, y);
}

//FacadeModele::obtenirInstance()->ajouterBonus(X1,Y1); break;

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////