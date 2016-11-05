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



	/// Accesseurs des options de debug
	bool isDebugActif();
	bool showCollisionRondelle();
	bool showVitesseRondelle();
	bool showEclairage();
	bool showAttractionPortail();




private:

	// Options de debug
	bool _isDebugActif;
	bool _showCollisionRondelle;
	bool _showVitesseRondelle;
	bool _showEclairage;
	bool _showAttractionPortail;
};


#endif // __CONFIGURATION_CONFIGDEBUG_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////