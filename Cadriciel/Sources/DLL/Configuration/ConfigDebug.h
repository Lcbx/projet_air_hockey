//////////////////////////////////////////////////////////////////////////////
/// @file ConfigDebug.h
/// @author Arthur Daniel-Adde
/// @date 2016-11-05
///
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGDEBUG_H__
#define __CONFIGURATION_CONFIGDEBUG_H__


#include "../../../Commun/Externe/tinyxml2/include/tinyxml2.h"


struct OptionsDebug {
	bool isDebugActif;
	bool showCollisionRondelle;
	bool showVitesseRondelle;
	bool showEclairage;
	bool showAttractionPortail;
};

///////////////////////////////////////////////////////////////////////////
/// @class ConfigDebug
/// @brief Représente les options de debug
///
/// @author Arthur Daniel-Adde
/// @date 2016-11-05
///////////////////////////////////////////////////////////////////////////
class ConfigDebug
{

public:

	/// Constructeur par défaut
	ConfigDebug();

	/// Charge les options de debug depuis le fichier de configuration.
	void chargerOptionsDebug();

	/// Modifie et sauvegarde les options de debug dans le fichier de configuration
	void setOptionsDebug(bool isDebugActif, bool showCollisionRondelle, bool showVitesseRondelle, bool showEclairage, bool showAttractionPortail);


	/// Accesseur des options de jeu
	struct OptionsDebug* getOptionsDebug();

	/// Accesseurs des options de debug indivuduels
	bool isDebugActif();
	bool showCollisionRondelle();
	bool showVitesseRondelle();
	bool showEclairage();
	bool showAttractionPortail();




private:

	// Options de debug
	OptionsDebug _optionsDebug;
};


#endif // __CONFIGURATION_CONFIGDEBUG_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////