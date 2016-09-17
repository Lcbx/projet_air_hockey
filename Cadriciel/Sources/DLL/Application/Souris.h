//////////////////////////////////////////////////////////////////////////////
/// @file Souris.h
/// @author Luc Courbariaux
/// @date 2016-09-12
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Selection.h"


namespace Souris {
	enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, DEBUT_AJOUT_MUR, AJOUT_MUR, DEBUT_AJOUT_PORTAIL, AJOUT_PORTAIL };
	Etats etatSouris = SELECTION;				//type d'operation en cours
	StrategieSouris* instance_ = new Selection;		//strategie

	static void EtatdelaSouris(int etat) {				//operation en cours
		etatSouris = static_cast<Etats>(etat);
		if (instance_ != nullptr) delete instance_;
		switch (etatSouris) {
		case SELECTION: { instance_ = new Selection;  break; }
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
			instance_ = nullptr;
		}
		}
	}

}

/*
// Click
class Souris {
public:
	enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, DEBUT_AJOUT_MUR, AJOUT_MUR, DEBUT_AJOUT_PORTAIL, AJOUT_PORTAIL};
	static Souris* obtenirInstance();		//singleton
	void libererInstance();					//singleton
	void startClick(int x, int y);			//les coordonnees du mouse_down
	void currentClick(int x, int y);		//les coordonnees du mouse_move
	void endClick(int x, int y);			//les coordonnees du mouse_up
	void  EtatdelaSouris(int etat);			//operation en cours

private:
	Souris();								//singleton
	static Souris* instance_;				//singleton
	StrategieSouris* notreStrategie_;		//strategie
	Etats etatSouris = SELECTION;			//type d'operation en cours
	void creerStrategie();					//actualise la strategie en cours	
};
*/