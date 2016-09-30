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
#include "glm/glm.hpp"

class StrategieSouris {
public:
	virtual void start(int x, int y);			//les coordonnees du mouse_down
	virtual void current(int x, int y);			//les coordonnees du mouse_move
	virtual void end(int x, int y);				//les coordonnees du mouse_up
	virtual void position(int x, int y);		//position de la souris hors d'un click
	bool plusDe3px(glm::ivec4 pos);				//indique si deux coordonnees sont eloignees de plus de 3 pixels
	bool plusDe3px();							//indique si nos coordonnees sont eloignees de plus de 3 pixels
	virtual void operationShortClick() = 0;		//lance l'opération adéquate selon le scénario du click
	virtual void operationDragClick() = 0;		//lance l'opération adéquate selon le scénario du click
	virtual void escEnfonce();					//interromp en cas de touche escape enfonce
protected:
	int& X1();
	int& Y1();
	int& X2();
	int& Y2();
};

