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
#include "Selection.h"

#include <glm/glm.hpp>


///////////////////////////////////////////////////////////////////////////
/// @class Souris
/// @brief Cette classe est une facade pour toues les classes
///         gérant l'utilisation de la souris
///
/// @author Luc Courbariaux
/// @date 2016-09-25
///////////////////////////////////////////////////////////////////////////
class Souris {
public:
	enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, AJOUT_MUR, AJOUT_PORTAIL, MISEAECHELLE, POINTSDECONTROLE, REDIMENSIONNEMENT, NBETATS };
	static Souris* obtenirInstance();		//singleton
	static void libererInstance();			//singleton
	void startClick(int x, int y);			//les coordonnees du mouse_down
	bool currentClick(int x, int y);		//les coordonnees du mouse_move
	void endClick(int x, int y);			//les coordonnees du mouse_up
	bool sourisPostition(int x, int y);		//position de la souris hors d'un click
	void EtatdelaSouris(int etat);			//operation en cours
	void clickRight(bool presse);			//change le type de clic (bouge la vue)
	void setControl(bool presse);			//change l'etat de la touche control
	bool getControl();						//donne l'etat de la touche control
	void setAlt(bool presse);			    //change l'etat de la touche alt
	bool getAlt();						    //donne l'etat de la touche alt
	void escPresse();						//permet de donner le signal que la touche escape est pressee
	glm::ivec4& getPosition();				//position de Click courante

private:
	Souris();								//singleton
	static Souris* instance_;				//singleton
	StrategieSouris* notreStrategie_;		//strategie
	Etats etatSouris = SELECTION;			//type d'operation en cours
	void creerStrategie();					//actualise la strategie en 
	bool boutonDroit_ = false; 				//click droit enfonce
	bool control_ = false;					//touche control enfoncee
	bool alt_ = false;					    //touche alt enfoncee
	glm::ivec4 position_;					//position de Click courante

	glm::dvec3 prevClicDroit_;				//Position précédente du clic droit
};
