//////////////////////////////////////////////////////////////////////////////
/// @file ConfigProfils.h
/// @author Arthur Daniel-Adde
/// @date 2016-11-04
///
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGPROFILS_H__
#define __CONFIGURATION_CONFIGPROFILS_H__

#include <list>
#include "../Application/Profil.h"

///////////////////////////////////////////////////////////////////////////
/// @class ConfigProfils
/// @brief Représente la liste des profils de joueurs virtuels
///
/// @author Arthur Daniel-Adde
/// @date 2016-11-04
///////////////////////////////////////////////////////////////////////////
class ConfigProfils
{

public:
	/// Constructeur par défaut
	ConfigProfils();






private:

	/// Liste des profils
	std::list<Profil> ListeProfils;



};
#endif