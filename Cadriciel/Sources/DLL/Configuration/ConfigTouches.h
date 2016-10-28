//////////////////////////////////////////////////////////////////////////////
/// @file ConfigTouches.h
/// @author Arthur Daniel-Adde
/// @date 2016-10-21
///
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGTOUCHES_H__
#define __CONFIGURATION_CONFIGTOUCHES_H__


#include "tinyxml2.h"

///////////////////////////////////////////////////////////////////////////
/// @class ConfigTouches
/// @brief Représente les touches utilisées par le joueur 2
///
/// @author Arthur Daniel-Adde
/// @date 2016-10-21
///////////////////////////////////////////////////////////////////////////
class ConfigTouches
{

public:


	/// Créer le DOM avec les valeurs (sauvegarde).
	void creerDOM(tinyxml2::XMLDocument& document);

	/// Lire les valeurs du DOM (chargement).
	void lireDOM(tinyxml2::XMLDocument const& document);

	/// Réinitialiser les touches du joueur 2
	void resetTouches();



	/// Accesseur de la touche haut
	int getToucheHaut();

	/// Accesseur de la touche droite
	int getToucheDroite();

	/// Accesseur de la touche bas
	int getToucheBas();

	/// Accesseur de la touche gauche
	int getToucheGauche();

	/// Accesseurs de toutes les touches
	void accederTouches(int &haut, int &droite, int &bas, int &gauche);

	/// Mutateur de la touche haut
	void setToucheHaut(int touche);

	/// Mutateur de la touche droite
	void setToucheDroite(int touche);

	/// Mutateur de la touche bas
	void setToucheBas(int touche);

	/// Mutateur de la touche gauche
	void setToucheGauche(int touche);

	/// Mutateur de toutes les touches
	void setTouches(int haut, int droite, int bas, int gauche);


	// Touches de déplacement pour le joueur 2 par défaut
	static int HAUTDEF;
	static int DROITEDEF;
	static int BASDEF;
	static int GAUCHEDEF;
	static 


private:

	// Touches de déplacement pour le joueur 2
	int _haut;
	int _droite;
	int _bas;
	int _gauche;
};


#endif // __CONFIGURATION_CONFIGTOUCHES_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
