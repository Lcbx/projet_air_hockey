//////////////////////////////////////////////////////////////////////////////
/// @file ConfigTouches.cpp
/// @author Arthur Daniel-Adde
/// @date 2016-10-21
///
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "ConfigTouches.h"
#include <iostream>


/// Nombre de calculs par image.
int ConfigTouches::HAUTDEF{ 1 };
int ConfigTouches::DROITEDEF{ 2 };
int ConfigTouches::BASDEF{ 3 };
int ConfigTouches::GAUCHEDEF{ 4 };


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::creerDOM ( TiXmlNode& node ) const
///
/// Cette methode sauvegarde les touches du jour 2 actuelles dans
///  un �l�ment XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigTouches::creerDOM(tinyxml2::XMLDocument& document) const
{
	// Cr�er le noeud 'configuration'
	tinyxml2::XMLElement* elementConfiguration{ document.NewElement("configuration") };

	// Cr�er le noeud 'touches' et d�finir ses attributs
	tinyxml2::XMLElement* elementTouches{ document.NewElement("CTouches") };
	elementTouches->SetAttribute("TOUCHE_HAUT", _haut);
	elementTouches->SetAttribute("TOUCHE_DROITE", _droite);
	elementTouches->SetAttribute("TOUCHE_BAS", _bas);
	elementTouches->SetAttribute("TOUCHE_GAUCHE", _gauche);

	// Adjoindre le noeud 'elementScene'
	elementConfiguration->LinkEndChild(elementTouches);

	// Adjoindre le noeud 'configuration' au noeud principal
	// (Rappel : pas besoin de lib�rer la m�moire de elementConfiguration
	// puisque toutes les fonctions Link... le font pour nous)
	document.LinkEndChild(elementConfiguration);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::lireDOM( const TiXmlNode& node )
///
/// Cette methode charge les touches du jour 2 actuelles � partir 
/// d'un �l�ment XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigTouches::lireDOM(const tinyxml2::XMLDocument& document)
{
	// Tenter d'obtenir le noeud 'Configuration'
	const tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
	if (elementConfiguration != nullptr) {
		// Tenter d'obtenir l'�l�ment 'touches', puis les attributs des touches
		const tinyxml2::XMLElement* elementTouches{ elementConfiguration->FirstChildElement("CTouches") };
		if (elementTouches != nullptr) {
			if (elementTouches->QueryIntAttribute("TOUCHE_HAUT", &_haut) != tinyxml2::XML_SUCCESS ||
				elementTouches->QueryIntAttribute("TOUCHE_DROITE", &_droite) != tinyxml2::XML_SUCCESS ||
				elementTouches->QueryIntAttribute("TOUCHE_BAS", &_bas) != tinyxml2::XML_SUCCESS ||
				elementTouches->QueryIntAttribute("TOUCHE_GAUCHE", &_gauche) != tinyxml2::XML_SUCCESS) {
				std::cerr << "Erreur de chargement des touches" << std::endl;
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn void ConfigTouches::resetTouches()
/// Cette methode permet de r�initialiser la valeur des diff�rentes
/// touches � leur valeur par d�faut
/// @return void
////////////////////////////////////////////////////////////////////////
void ConfigTouches::resetTouches()
{
	_haut = HAUTDEF;
	_droite - DROITEDEF;
	_bas = BASDEF;
	_gauche = GAUCHEDEF;
}


////////////////////////////////////////////////////////////////////////
/// @fn int ConfigTouches::getToucheHaut()
/// Cette methode permet d'obtenir la touche correspondant � la
/// direction "haut" du joueur 2.
/// @return la touche haut
////////////////////////////////////////////////////////////////////////
int ConfigTouches::getToucheHaut()
{
	return _haut;
}

////////////////////////////////////////////////////////////////////////
/// @fn int ConfigTouches::getToucheDroite()
/// Cette methode permet d'obtenir la touche correspondant � la
/// direction "droite" du joueur 2.
/// @return la touche droite
////////////////////////////////////////////////////////////////////////
int ConfigTouches::getToucheDroite()
{
	return _droite;
}

////////////////////////////////////////////////////////////////////////
/// @fn int ConfigTouches::getToucheBas()
/// Cette methode permet d'obtenir la touche correspondant � la
/// direction "bas" du joueur 2.
/// @return la touche bas
////////////////////////////////////////////////////////////////////////
int ConfigTouches::getToucheBas()
{
	return _bas;
}

////////////////////////////////////////////////////////////////////////
/// @fn int ConfigTouches::getToucheGauche()
/// Cette methode permet d'obtenir la touche correspondant � la
/// direction "gauche" du joueur 2.
/// @return la touche gauche
////////////////////////////////////////////////////////////////////////
int ConfigTouches::getToucheGauche()
{
	return _gauche;
}


////////////////////////////////////////////////////////////////////////
/// @fn void ConfigTouches::setToucheHaut()
/// Cette methode permet de modifier la touche correspondant � la
/// direction "haut" du joueur 2.
/// @param[in] touche : nouvelle touche haut
/// @return void
////////////////////////////////////////////////////////////////////////
void ConfigTouches::setToucheHaut(int touche)
{
	_haut = touche;
}

////////////////////////////////////////////////////////////////////////
/// @fn void ConfigTouches::setToucheDroite()
/// Cette methode permet de modifier la touche correspondant � la
/// direction "droite" du joueur 2.
/// @param[in] touche : nouvelle touche droite
/// @return void
////////////////////////////////////////////////////////////////////////
void ConfigTouches::setToucheDroite(int touche)
{
	_droite = touche;
}

////////////////////////////////////////////////////////////////////////
/// @fn void ConfigTouches::setToucheBas()
/// Cette methode permet de modifier la touche correspondant � la
/// direction "bas" du joueur 2.
/// @param[in] touche : nouvelle touche bas
/// @return void
////////////////////////////////////////////////////////////////////////
void ConfigTouches::setToucheBas(int touche)
{
	_bas = touche;
}

////////////////////////////////////////////////////////////////////////
/// @fn void ConfigTouches::setToucheGauche()
/// Cette methode permet de modifier la touche correspondant � la
/// direction "gauche" du joueur 2.
/// @param[in] touche : nouvelle touche gauche
/// @return void
////////////////////////////////////////////////////////////////////////
void ConfigTouches::setToucheGauche(int touche)
{
	_gauche = touche;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
