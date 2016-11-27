///////////////////////////////////////////////////////////////////////////////
/// @file Sons.cpp
/// @author Wajdi Gharsalli
/// @date 17-11-2016
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Sons.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn Sons::Sons()
///
/// constructeur par defaut
///
/// @return rien
///
/////////////////////////////////////////////////////////////////////////
Sons::Sons()
{
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(system, "media/sons/pine.wav", FMOD_CREATESAMPLE, 0, &mur);
	FMOD_System_CreateSound(system, "media/sons/veet.wav", FMOD_CREATESAMPLE, 0, &portail);
	FMOD_System_CreateSound(system, "media/sons/speed.wav", FMOD_CREATESAMPLE, 0, &bonus);
	FMOD_System_CreateSound(system, "media/sons/clap.wav", FMOD_CREATESAMPLE, 0, &maillet);
	FMOD_System_CreateSound(system,"media/sons/beatIt.wav", FMOD_LOOP_NORMAL| FMOD_SOFTWARE, 0, &musiqueFond);
	FMOD_System_CreateSound(system, "media/sons/applo.wav", FMOD_CREATESAMPLE, 0, &but);

/*	FMOD_System_CreateSound(system, "media/sons/beatIt.wav", FMOD_SOFTWARE 
		| FMOD_2D | FMOD_CREATESTREAM, 0, &musiqueFond);*/
	FMOD_System_GetMasterChannelGroup(system, &canal);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn Sons::~Sons()
///
/// Destructeur
///
/// @return rien
///
/////////////////////////////////////////////////////////////////////////
Sons::~Sons()
{
	FMOD_Sound_Release(mur);
	FMOD_Sound_Release(portail);
	FMOD_Sound_Release(bonus);
	FMOD_Sound_Release(maillet);
	FMOD_Sound_Release(but);
	FMOD_Sound_Release(musiqueFond);

	FMOD_System_Close(system);
	FMOD_System_Release(system);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sons::jouerSon(int choix)
///
/// permet de jouer le son selon la valeur passée en parametres 
///
/// @return rien
///
/////////////////////////////////////////////////////////////////////////
void Sons::jouerSon(int choix)
{
	switch (choix) {
	case 1:
	{
		FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, mur, 0, NULL);
		break;}
	case 2:
	{
		FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, portail, 0, NULL);
		break;}
	case 3:
	{	
		//FMOD_Sound_SetLoopCount(musiqueFond, -1);
		FMOD_ChannelGroup_SetPaused(canal, 0);
		FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiqueFond, 0, NULL);
		break; }
	case 4:
	{
		FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bonus, 0, NULL);
		break; }
	case 5:
	{
		FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, maillet, 0, NULL);
		break; }
	case 6:
	{
		FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, but, 0, NULL);
		break; }
	default:
		break;

	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Sons::pauseSon(bool pause)
///
///mettre le son de fond en pause 
///
/// @return rien
///
/////////////////////////////////////////////////////////////////////////
void Sons::pauseSon(bool pause)
{
	if (pause == true) // Si la chanson est en pause
	{
		FMOD_ChannelGroup_SetPaused(canal, 0);
	}// On enlève la pause
	else // Sinon, elle est en cours de lecture
	{
		FMOD_ChannelGroup_SetPaused(canal, 1);
	}// On active la pause*/

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Sons::arreterSon(bool pause)
///
///arreter le son de fond en pause 
///
/// @return rien
///
/////////////////////////////////////////////////////////////////////////
void Sons::arreterSon()
{
	FMOD_ChannelGroup_SetPaused(canal, 0);
	FMOD_ChannelGroup_Stop(canal);
}