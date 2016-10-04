///////////////////////////////////////////////////////////////////////////////
/// @file POintsControle.h
/// @author Luc Courbariaux
/// @date 2016-09-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "StrategieSouris.h"
#include "../Noeuds/NoeudPointControle.h"

class NoeudPointControle;

class PointsControle : public StrategieSouris {
public:
	void start(int x, int y);				//les coordonnees du mouse_down
	void current(int x, int y);				//les coordonnees du mouse_move
	void end(int x, int y);					//les coordonnees du mouse_up
	//void position(int x, int y);			//position de la souris hors d'un click
	void operationShortClick();				//lance l'opération adéquate selon le scénario du click
	void operationDragClick();				//lance l'opération adéquate selon le scénario du click
private:
	//int X1, Y1, X2, Y2;					//pour garder l'information des points du Click
	const int PASDENOEUD = -1;				//une constante poour dire qu'il n'y a pas de noeud selectionnne
	int noeud_{ PASDENOEUD };				//numero du noeud selectionne
	NoeudPointControle* p(int i);			//obtenir le point de controle correspondant
	glm::vec3 pos(int i);					//recupere la position du point de controle i
};

