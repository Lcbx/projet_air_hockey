///////////////////////////////////////////////////////////////////////////////
/// @file Duplication.h
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "StrategieSouris.h"
#include "../VisiteurDuplication.h"

///////////////////////////////////////////////////////////////////////////
/// @class Duplication
/// @brief Cette classe contient des m�thodes permettant de dupliquer
///        des objets avec la souris
///
/// @author Luc Courbariaux
/// @date 2016-09-25
///////////////////////////////////////////////////////////////////////////
class Duplication : public StrategieSouris {
public:
	Duplication(){}
	void start(int x, int y);				//les coordonnees du mouse_down
	void current(int x, int y);				//les coordonnees du mouse_move
	void end(int x, int y);					//les coordonnees du mouse_up
	void escEnfonce();						//interromp pour changement de mode
	//void position(int x, int y);			//position de la souris hors d'un click
	void operationShortClick();				//lance l'op�ration ad�quate selon le sc�nario du click
	void operationDragClick();				//lance l'op�ration ad�quate selon le sc�nario du click
private:
	//int X1, Y1, X2, Y2;					//pour garder l'information des points du Click
	VisiteurDuplication visiteur_;
};
