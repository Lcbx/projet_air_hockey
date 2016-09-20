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
	enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, DEBUT_AJOUT_MUR, AJOUT_MUR, DEBUT_AJOUT_PORTAIL, AJOUT_PORTAIL};
	static Souris* obtenirInstance();
	void libererInstance();
	void startClick(int x, int y);			//les coordonnees du mouse_down
	void currentClick(int x, int y);		//les coordonnees du mouse_move
	void endClick(int x, int y);			//les coordonnees du mouse_up
	bool plusDe3px();						//indique s'il faut afficher un rectangle de sélection
	void EtatdelaSouris(int etat);			//permet de connaitre l'opération a realiser lors d'un click
	void operationShortClick();				//lance l'opération adéquate selon le scénario du click
	void operationDragClick();				//lance l'opération adéquate selon le scénario du click

private:
	bool controlPresse();
	int X1, Y1, X2, Y2;						//pour garder l'information des points du rectangle élastique
	bool effacerDernierRectangle=false;		//pour permettre la transition au dessus de 3 pixels
	Etats etatSouris = SELECTION;			//type d'operation en cours
	//singleton
	Souris();
	static Souris* instance_;
};