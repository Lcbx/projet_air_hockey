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
#include "Selection.h"
#include "AjoutAccelerateur.h"
#include "DebutAjoutMur.h"
#include "AjoutMur.h"
#include "DebutAjoutPortail.h"
#include "AjoutPortail.h"
///////////////////////////////////////////////////////////////////////////////
/// @file Souris.cpp
/// @author Luc Courbariaux
/// @date 2016-09-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


#include "glm\glm.hpp"
#include "../VisiteurSelection.h"
#include "Duplication.h"
#include "Rotation.h"
#include "Loupe.h"
#include "Deplacement.h"



Souris* Souris::instance_{ nullptr };

Souris::Souris() {
	creerStrategie();
};

Souris* Souris::obtenirInstance() {
	if (instance_ == nullptr) instance_ = new Souris;
	return instance_;
}

void Souris::libererInstance() {
	delete instance_->notreStrategie_;
	instance_->notreStrategie_ = nullptr;
	delete instance_;
	instance_ = nullptr;
}

void Souris::EtatdelaSouris(int etat) {
	etatSouris = static_cast<Etats>(etat);
	if (notreStrategie_ != nullptr) delete notreStrategie_;
	creerStrategie();
}


void Souris::creerStrategie(){
	switch (etatSouris) {
	case SELECTION: {			notreStrategie_ = new Selection;  break; }
	case LOUPE: {				notreStrategie_ = new Loupe; break; }
	case DEPLACEMENT: {			notreStrategie_ = new Deplacement; break; }
	case ROTATION: {			notreStrategie_ = new Rotation; break; }
	case DUPLICATION: {			notreStrategie_ = new Duplication; break; }
	case AJOUT_ACCELERATEUR: {	notreStrategie_ = new AjoutAccelerateur; break; }
	case DEBUT_AJOUT_MUR: {		notreStrategie_ = new DebutAjoutMur; break; }
	case AJOUT_MUR: {			notreStrategie_ = new AjoutMur; break; }
	case DEBUT_AJOUT_PORTAIL: {	notreStrategie_ = new DebutAjoutPortail; break; }
	case AJOUT_PORTAIL: {		notreStrategie_ = new AjoutPortail; break; }
	default: {	notreStrategie_ = nullptr; break;  }
	}
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

void Souris::sourisPostition(int x, int y) {
	notreStrategie_->position(x, y);
}

void Souris::setControl(bool presse) {
	control_ = presse;
}

bool Souris::getControl() {
	return control_;
}

void Souris::escPresse() {
	notreStrategie_->escEnfonce();
}


glm::ivec4& Souris::getPosition() {
	return position_;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
