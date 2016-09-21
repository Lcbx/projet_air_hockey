///////////////////////////////////////////////////////////////////////////////
/// @file Selection.h
/// @author Luc Courbariaux
/// @date 2016-09-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once


class StrategieSouris {
public:
	virtual void start(int x, int y);			//les coordonnees du mouse_down
	virtual void current(int x, int y);			//les coordonnees du mouse_move
	virtual void end(int x, int y);				//les coordonnees du mouse_up
	virtual void position(int x, int y);		//position de la souris hors d'un click
	bool plusDe3px();							//indique s'il faut afficher un rectangle de sélection
	virtual void operationShortClick() = 0;		//lance l'opération adéquate selon le scénario du click
	virtual void operationDragClick() = 0;		//lance l'opération adéquate selon le scénario du click
protected:
	int X1, Y1, X2, Y2;							//pour garder l'information des points du Click
};

