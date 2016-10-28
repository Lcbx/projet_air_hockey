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
#include "AjoutMur.h"
#include "AjoutPortail.h"
#include "Duplication.h"
#include "Rotation.h"
#include "Loupe.h"
#include "Deplacement.h"
#include "../MiseEchelle.h"
#include "PointsControle.h"
#include "../Test.h"

#include "../Application/FacadeModele.h"
#include "../Vue/Vue.h"
#include "../Vue/Camera.h"
#include "../ArbreRenduINF2990.h"


//initialisation du patron singleton
Souris* Souris::instance_{ nullptr };


////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::Souris()
///
/// crait la souris et la strategie utilisée (selection, deplacement , rotation, ...)
///
/// @return Aucune (Constructeur).
///
/////////////////////////////////////////////////////////////////////////
Souris::Souris() {
	creerStrategie();
};

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::obtenirInstance()
///
/// donne un pointeur vers l'instance de Souris (singleton)
///
/// @return Souris*
///
/////////////////////////////////////////////////////////////////////////
Souris* Souris::obtenirInstance() {
	if (instance_ == nullptr) instance_ = new Souris;
	return instance_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::libererInstance()
///
/// libere l'instance de Souris (singleton)
///
/// @return aucune
///
/////////////////////////////////////////////////////////////////////////
void Souris::libererInstance() {
	if (instance_ != nullptr) {
		if (instance_->notreStrategie_ != nullptr) {
			delete instance_->notreStrategie_;
			instance_->notreStrategie_ = nullptr;
		}
		delete instance_;
		instance_ = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::EtatdelaSouris(int etat)
///
/// change la strategie utilisée (selection, deplacement , rotation, ...)
///
/// @return Aucune (Constructeur).
///
/////////////////////////////////////////////////////////////////////////
void Souris::EtatdelaSouris(int etat) {
	escPresse(); //evite de garder un portail non fini
	etatSouris = static_cast<Etats>(etat);
	if (notreStrategie_ != nullptr) delete notreStrategie_;
	creerStrategie();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::creerStrategie()
///
/// crait la strategie utilisée (selection, deplacement , rotation, ...)
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::creerStrategie(){
	switch (etatSouris) {
	case SELECTION: {			notreStrategie_ = new Selection;  break; }
	case LOUPE: {				notreStrategie_ = new Loupe; break; }
	case DEPLACEMENT: {			notreStrategie_ = new Deplacement; break; }
	case ROTATION: {			notreStrategie_ = new Rotation; break; }
	case DUPLICATION: {			notreStrategie_ = new Duplication; break; }
	case AJOUT_ACCELERATEUR: {	notreStrategie_ = new AjoutAccelerateur; break; }
	case AJOUT_MUR: {			notreStrategie_ = new AjoutMur; break; }
	case AJOUT_PORTAIL: {		notreStrategie_ = new AjoutPortail; break; }
	case MISEAECHELLE: {		notreStrategie_ = new MiseEchelle; break; }
	case POINTSDECONTROLE: {	notreStrategie_ = new PointsControle; break; }
	case TEST: {				notreStrategie_ = new Test; break; }

	default: {	throw("Souris::strategie inconnue demandee"); break;  }
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::startClick(int x, int y)
///
/// appelle la fonction start de la strategie utilisée (selection, deplacement , rotation, ...)
/// et gere le click droit
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::startClick(int x, int y) {
	if (!boutonDroit_) notreStrategie_->start(x, y);
	else {
		//traitement du bouton droit
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, prevClicDroit_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::currentClick(int x, int y)
///
/// appelle la fonction current de la strategie utilisée (selection, deplacement , rotation, ...)
/// et gere le click droit, renvoie si le clic est dans la table
///
/// @return bool
///
/////////////////////////////////////////////////////////////////////////
bool Souris::currentClick(int x, int y) {
	glm::dvec3 click{ 0,0,0 }; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, click);
	if(!boutonDroit_) notreStrategie_->current( x, y);
	else {
		//traitement du bouton droit
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCamera().deplacerXY((prevClicDroit_ - click).x, (prevClicDroit_ - click).y, true);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, prevClicDroit_);
	}
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(click);
	return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(click);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::endClick(int x, int y)
///
/// appelle la fonction end de la strategie utilisée (selection, deplacement , rotation, ...)
/// et gere le click droit
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::endClick(int x, int y) {
	if (!boutonDroit_) notreStrategie_->end(x, y);
	else { }
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::sourisPostition(int x, int y)
///
/// appelle la fonction position de la strategie utilisée (selection, deplacement , rotation, ...)
/// et gere le click droit, renvoie si le clic est dans la table
///
/// @return bool
///
/////////////////////////////////////////////////////////////////////////
bool Souris::sourisPostition(int x, int y) {
	glm::dvec3 click{ 0,0,0 }; FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, click);
	if (!boutonDroit_) notreStrategie_->position(x, y);
	else {
		//traitement du bouton droit
	}
	return FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable()->dansTable(click);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::clickRight(bool presse)
///
/// appelé par la couche C# pour signifier que le bouton droit est pressé
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::clickRight(bool presse) {
	boutonDroit_ = presse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::setControl(bool presse)
///
/// appelé par la couche C# pour signifier que la touche control est pressé
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::setControl(bool presse) {
	control_ = presse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::getControl()
///
/// permet de connaitre si la touche control est presse
///
/// @return bool
///
/////////////////////////////////////////////////////////////////////////
bool Souris::getControl() {
	return control_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::setAlt(bool presse)
///
/// appelé par la couche C# pour signifier que la touche Alt est pressé
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::setAlt(bool presse) {
	alt_ = presse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::getControl()
///
/// permet de connaitre si la touche Alt est presse
///
/// @return bool
///
/////////////////////////////////////////////////////////////////////////
bool Souris::getAlt() {
	return alt_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::escPresse(bool presse)
///
/// appelé par la couche C# pour signifier que la touche echap est pressé
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::escPresse() {
	notreStrategie_->escEnfonce();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::getPosition()
///
/// retourne la position de la souris
///
/// @return glm::ivec4&
///
/////////////////////////////////////////////////////////////////////////
glm::ivec4& Souris::getPosition() {
	return position_;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
