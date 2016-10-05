///////////////////////////////////////////////////////////////////////////////
/// @file AjoutAccelerateur.h
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "StrategieSouris.h"


///////////////////////////////////////////////////////////////////////////
/// @class AjoutAccelerateur
/// @brief Cette classe contient des méthodes permettant d'ajouter
///        un bonus accelerateur avec la souris
///
/// @author Luc Courbariaux
/// @date 2016-09-25
///////////////////////////////////////////////////////////////////////////
class AjoutAccelerateur : public StrategieSouris {
public:
	//void start(int x, int y);				//les coordonnees du mouse_down
	//void current(int x, int y);			//les coordonnees du mouse_move
	//void end(int x, int y);				//les coordonnees du mouse_up
	void operationShortClick();				//lance l'opération adéquate selon le scénario du click
	void operationDragClick();				//lance l'opération adéquate selon le scénario du click
private:
	//int X1, Y1, X2, Y2;					//pour garder l'information des points du Click
};