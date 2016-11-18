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


Sons::Sons()
{
	std::cout << "Constructor" << std::endl;

	FMOD_System_Create(&system);
	FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(system, "media/sons/pine.wav", FMOD_CREATESAMPLE, 0, &mur);
	FMOD_System_CreateSound(system, "media/sons/veet.wav", FMOD_CREATESAMPLE, 0, &portail);
	FMOD_System_CreateSound(system,"media/sons/beatIt.wav", FMOD_LOOP_NORMAL, 0, &musiqueFond);


}

Sons::~Sons()
{
	std::cout << "Destructor" << std::endl;

	FMOD_Sound_Release(mur);
	FMOD_Sound_Release(portail);
	FMOD_Sound_Release(musiqueFond);

	FMOD_System_Close(system);
	FMOD_System_Release(system);
}

void Sons::jouerSon(int choix)
{
	std::cout << "Dans jouer" << std::endl;

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
		//FMOD_Sound_SetLoopCount(musiqueFond, -1)
		FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiqueFond, 0, NULL);

		break; }
	default:
		break;

	}
}

void Sons::arreterSon()
{


}