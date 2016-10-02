///////////////////////////////////////////////////////////////////////////////
/// @file MiseEchelle.h
/// @author Wajdi Gharsalli	
/// @date 2016-09-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "StrategieSouris.h"
#include "../VisiteurMiseEchelle.h"

class MiseEchelle : public StrategieSouris {
public:
	//void start(int x, int y);				//les coordonnees du mouse_down
	void current(int x, int y);				//les coordonnees du mouse_move
											//void end(int x, int y);				//les coordonnees du mouse_up
											//void position(int x, int y);			//position de la souris hors d'un click
	void operationShortClick();				//lance l'op�ration ad�quate selon le sc�nario du click
	void operationDragClick();				//lance l'op�ration ad�quate selon le sc�nario du click
private:
	//int X1, Y1, X2, Y2;					//pour garder l'information des points du Click
	VisiteurMiseEchelle visiteur_;
};
