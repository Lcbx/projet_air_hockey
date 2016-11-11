//////////////////////////////////////////////////////////////////////////////
/// @file ConfigJeu.h
/// @author Arthur Daniel-Adde
/// @date 2016-11-05
///
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGJEU_H__
#define __CONFIGURATION_CONFIGJEU_H__


#include "../../../Commun/Externe/tinyxml2/include/tinyxml2.h"


struct OptionsJeu {
	int nbrBut;
	bool joueurTestEstHumain;
};


///////////////////////////////////////////////////////////////////////////
/// @class ConfigJeu
/// @brief Représente les options de jeu
///
/// @author Arthur Daniel-Adde
/// @date 2016-11-05
///////////////////////////////////////////////////////////////////////////
class ConfigJeu
{
public:

	/// Constructeur par défaut
	ConfigJeu();

	/// Charge les options de jeu depuis le fichier de configuration.
	void chargerOptionsJeu();

	/// Modifie et sauvegarde les options de jeu dans le fichier de configuration
	void setOptionsJeu(int nbrBut, bool joueurTestEstHumain);


	/// Accesseur des options de jeu
	struct OptionsJeu* getOptionsJeu();

	/// Accesseur du nombre de but
	int getNombreDeButs();

	/// Accesseur du type de joueur
	bool joueurTestEstHumain();



	// Constantes des options de jeu par défaut
	static const int NOMBRE_BUT_DEFAUT;
	static const bool JOUEUR_TEST_EST_HUMAIN_DEFAUT;



private:

	// Options de jeu
	struct OptionsJeu _optionsJeu;
};


#endif // __CONFIGURATION_CONFIGJEU_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////