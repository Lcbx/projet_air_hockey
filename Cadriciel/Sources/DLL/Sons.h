///////////////////////////////////////////////////////////////////////////////
/// @file Sons.h
/// @author Wajdi Gharsalli	
/// @date 17-11-2016
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "fmod.h" 


///////////////////////////////////////////////////////////////////////////
/// @class Sons
/// @brief cette classe permet de jouer des sons 
///
/// @author Wajdi Gharsalli
/// @date 17-11-2016
///////////////////////////////////////////////////////////////////////////
class Sons  {

public:
	///Constructeur par defaut 
	Sons();
	///destructeur
	~Sons();
	///Permet de jouer le son
	void jouerSon(int choix);
	///mettre le son en pause
	void pauseSon(bool pause);
	///arreter le son
	void arreterSon();

private:
	FMOD_SYSTEM *system;
	
	FMOD_SOUND *mur;
	FMOD_SOUND  *portail;
	FMOD_SOUND  *bonus;
	FMOD_SOUND  *maillet;
	FMOD_SOUND  *but;
	FMOD_SOUND  *musiqueFond;

	FMOD_CHANNELGROUP *canal;

};
