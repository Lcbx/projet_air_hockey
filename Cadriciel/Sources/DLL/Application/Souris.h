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
#include "Selection.h"

#include <glm/glm.hpp>


// Click
class Souris {
public:
	enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, DEBUT_AJOUT_MUR, AJOUT_MUR, DEBUT_AJOUT_PORTAIL, AJOUT_PORTAIL};
	static Souris* obtenirInstance();		//singleton
	static void libererInstance();			//singleton
	void startClick(int x, int y);			//les coordonnees du mouse_down
	void currentClick(int x, int y);		//les coordonnees du mouse_move
	void endClick(int x, int y);			//les coordonnees du mouse_up
	void sourisPostition(int x, int y);		//position de la souris hors d'un click
	void EtatdelaSouris(int etat);			//operation en cours
	void setControl(bool presse);			//change l'etat de la touche control
	bool getControl();						//donne l'etat de la touche control
	glm::ivec4& getPosition();				//position de Click courante

private:
	Souris();								//singleton
	static Souris* instance_;				//singleton
	StrategieSouris* notreStrategie_;		//strategie
	Etats etatSouris = SELECTION;			//type d'operation en cours
	void creerStrategie();					//actualise la strategie en cours
	bool control_ = false;					//touche control enfoncee
	glm::ivec4 position_;					//position de Click courante
};
