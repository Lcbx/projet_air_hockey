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

// Click
class Selection {
	int X_ = 0, Y_ = 0;	 //pour garder l'information (rectangle élastique)
	Selection();
	static Selection* instance_;
public:
	static Selection* obtenirInstance();
	void libererInstance();
	void startClick(int x, int y);			//les coordonnees du mouse_down
	void currentClick(int x, int y);		//les coordonnees du mouse_move
	void endClick(int x, int y);			//les coordonnees du mouse_up
};