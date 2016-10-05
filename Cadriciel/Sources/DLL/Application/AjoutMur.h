///////////////////////////////////////////////////////////////////////////////
/// @file AjoutMur.h
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "StrategieSouris.h"
#include "glm/glm.hpp"

class AjoutMur : public StrategieSouris {
public:
	void start(int x, int y);			//les coordonnees du mouse_down
	void current(int x, int y);			//les coordonnees du mouse_move
	void end(int x, int y);				//les coordonnees du mouse_up
	void position(int x, int y);		//position de la souris hors d'un click
	void operationShortClick();			//lance l'op�ration ad�quate selon le sc�nario du click
	void operationDragClick();			//lance l'op�ration ad�quate selon le sc�nario du click
	void escEnfonce();					//au cas ou si on doit arreter l'ajout
private:
	//int X1, Y1, X2, Y2;				//pour garder l'information des points du Click
	glm::ivec4 notrePosition_;			//pour garder la position du premier click
	bool clickInitial = true;			//distinction entre les deux clicks
	bool estEnfonce = false;
};
