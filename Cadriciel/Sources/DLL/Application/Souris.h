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
#include "AideGL.h"

// Click
class Souris {
public:
	enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, AJOUT_MUR, AJOUT_PORTAIL };
	static Souris* obtenirInstance();
	void libererInstance();
	void startClick(int x, int y);			//les coordonnees du mouse_down
	void currentClick(int x, int y);		//les coordonnees du mouse_move
	void endClick(int x, int y);			//les coordonnees du mouse_up
	bool rectangleSelection();				//indique s'il faut afficher un rectangle de sélection
	void EtatdelaSouris(int etat);			//temp : etat de la souris

private:
	int X1, Y1, X2, Y2;						//pour garder l'information des points du rectangle élastique
	bool effacerDernierRectangle;			//pour permettre la transition au dessus de 3 pixels
	Etats etatSouris = SELECTION;			//type d'operation en cours
	//singleton
	Souris();
	static Souris* instance_;
};