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
	bool plusDe3px();							//indique s'il faut afficher un rectangle de sélection
	virtual void operationShortClick() = 0;		//lance l'opération adéquate selon le scénario du click
	virtual void operationDragClick() = 0;		//lance l'opération adéquate selon le scénario du click
private:
	int X1, Y1, X2, Y2;							//pour garder l'information des points du Click
};

bool StrategieSouris::plusDe3px() {
	return (X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2) > 9;
}

void StrategieSouris::start(int x, int y) {
	//initialisation du clic
	X1 = x; Y1 = y;
	X2 = x; Y2 = y;
}

void StrategieSouris::current(int x, int y) {
	X2 = x; Y2 = y;
}

void StrategieSouris::end(int x, int y) {
	X2 = x; Y2 = y;
	//opération
	plusDe3px() ? operationDragClick() : operationShortClick();
}