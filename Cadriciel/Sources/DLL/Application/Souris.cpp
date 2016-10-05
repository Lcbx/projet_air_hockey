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



//initialisation du patron singleton
Souris* Souris::instance_{ nullptr };


////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::Souris()
///
/// crait la souris et la strategie utilis�e (selection, deplacement , rotation, ...)
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
/// change la strategie utilis�e (selection, deplacement , rotation, ...)
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
/// crait la strategie utilis�e (selection, deplacement , rotation, ...)
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
	default: {	throw("Souris::strategie inconnue demandee"); break;  }
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::startClick(int x, int y)
///
/// appelle la fonction start de la strategie utilis�e (selection, deplacement , rotation, ...)
/// et gere le click droit
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::startClick(int x, int y) {
	if (!boutonDroit_) notreStrategie_->start(x, y);
	else {
		//traitement du bouton droit
		std::cout << "debut click droit\n";


	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::currentClick(int x, int y)
///
/// appelle la fonction current de la strategie utilis�e (selection, deplacement , rotation, ...)
/// et gere le click droit
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::currentClick(int x, int y) {
	if(!boutonDroit_) notreStrategie_->current( x, y);
	else {
		//traitement du bouton droit
		//std::cout << "pendant click droit\n";


	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::endClick(int x, int y)
///
/// appelle la fonction end de la strategie utilis�e (selection, deplacement , rotation, ...)
/// et gere le click droit
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::endClick(int x, int y) {
	if (!boutonDroit_) notreStrategie_->end(x, y);
	else {
		//traitement du bouton droit
		std::cout << "fin click droit\n";


	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::sourisPostition(int x, int y)
///
/// appelle la fonction position de la strategie utilis�e (selection, deplacement , rotation, ...)
/// et gere le click droit
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void Souris::sourisPostition(int x, int y) {
	if (!boutonDroit_) notreStrategie_->position(x, y);
	else {
		//traitement du bouton droit
		//std::cout << "en dehors du click droit\n;

		
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Souris::clickRight(bool presse)
///
/// appel� par la couche C# pour signifier que le bouton droit est press�
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
/// appel� par la couche C# pour signifier que la touche control est press�
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
/// appel� par la couche C# pour signifier que la touche Alt est press�
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
/// appel� par la couche C# pour signifier que la touche echap est press�
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
