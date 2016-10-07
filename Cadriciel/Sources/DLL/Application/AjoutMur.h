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


///////////////////////////////////////////////////////////////////////////
/// @class AjoutMur
/// @brief Cette classe contient des méthodes permettant d'ajouter
///        un mur avec la souris
///
/// @author Luc Courbariaux
/// @date 2016-09-25
///////////////////////////////////////////////////////////////////////////
class AjoutMur : public StrategieSouris {
public:
	///les coorsonnées du mouse_down
	void start(int x, int y);
	///les coordonnees du mouse_move
	void current(int x, int y);
	///les coordonnees du mouse_up
	void end(int x, int y);
	///position de la souris hors d'un click
	void position(int x, int y);
	///lance l'opération adéquate selon le scénario du click
	void operationShortClick();
	///lance l'opération adéquate selon le scénario du click
	void operationDragClick();
	///au cas ou si on doit arreter l'ajout
	void escEnfonce();					
private:
	///int X1, Y1, X2, Y2; pour garder l'information des points du Click
	///pour garder la position du premier click
	glm::ivec4 notrePosition_;
	///distinction entre les deux clicks 
	bool clickInitial_ = true;
	///premier affichage su muret fantome
	bool premierAffichage_ = true;
};
