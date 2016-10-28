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
int ConfigTouches::HAUTDEF{ 87 };
int ConfigTouches::DROITEDEF{ 68 };
int ConfigTouches::BASDEF{ 83 };
int ConfigTouches::GAUCHEDEF{ 65 };


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::creerDOM ( TiXmlNode& node ) const
///
/// Cette methode sauvegarde les touches du jour 2 actuelles dans
///  un élément XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigTouches::creerDOM(tinyxml2::XMLDocument& document)
{
	// Créer le noeud 'configuration'
	tinyxml2::XMLElement* elementConfiguration{ document.NewElement("configuration") };

	// Créer le noeud 'touches' et définir ses attributs
	tinyxml2::XMLElement* elementTouches{ document.NewElement("CTouches") };
	elementTouches->SetAttribute("TOUCHE_HAUT", _haut);
	elementTouches->SetAttribute("TOUCHE_DROITE", _droite);
	elementTouches->SetAttribute("TOUCHE_BAS", _bas);
	elementTouches->SetAttribute("TOUCHE_GAUCHE", _gauche);

	// Adjoindre le noeud 'elementScene'
	elementConfiguration->LinkEndChild(elementTouches);

	// Adjoindre le noeud 'configuration' au noeud principal
	// (Rappel : pas besoin de libérer la mémoire de elementConfiguration
	// puisque toutes les fonctions Link... le font pour nous)
	document.LinkEndChild(elementConfiguration);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::lireDOM( const TiXmlNode& node )
///
/// Cette methode charge les touches du jour 2 actuelles à partir 
/// d'un élément XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigTouches::lireDOM(const tinyxml2::XMLDocument& document)
{
	// Tenter d'obtenir le noeud 'Configuration'
	const tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
	if (elementConfiguration != nullptr) {
		// Tenter d'obtenir l'élément 'touches', puis les attributs des touches
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
/// Cette methode permet de réinitialiser la valeur des différentes
/// touches à leur valeur par défaut
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
/// Cette methode permet d'obtenir la touche correspondant à la
/// direction "haut" du joueur 2.
/// @return la touche haut
////////////////////////////////////////////////////////////////////////
int ConfigTouches::getToucheHaut()
{
	return _haut;
}

////////////////////////////////////////////////////////////////////////
/// @fn int ConfigTouches::getToucheDroite()
/// Cette methode permet d'obtenir la touche correspondant à la
/// direction "droite" du joueur 2.
/// @return la touche droite
////////////////////////////////////////////////////////////////////////
int ConfigTouches::getToucheDroite()
{
	return _droite;
}

////////////////////////////////////////////////////////////////////////
/// @fn int ConfigTouches::getToucheBas()
/// Cette methode permet d'obtenir la touche correspondant à la
/// direction "bas" du joueur 2.
/// @return la touche bas
////////////////////////////////////////////////////////////////////////
int ConfigTouches::getToucheBas()
{
	return _bas;
}

////////////////////////////////////////////////////////////////////////
/// @fn int ConfigTouches::getToucheGauche()
/// Cette methode permet d'obtenir la touche correspondant à la
/// direction "gauche" du joueur 2.
/// @return la touche gauche
////////////////////////////////////////////////////////////////////////
int ConfigTouches::getToucheGauche()
{
	return _gauche;
}

////////////////////////////////////////////////////////////////////////
/// @fn void ConfigTouches::accederTouches()
/// Cette methode permet d'obtenir les touches correspondants aux
/// 4 direction
/// @param[out] haut : Touche haut
/// @param[out] droite : Touche droite
/// @param[out] bas : Touche bas
/// @param[out] gauche : Touche gauche
/// @return void
////////////////////////////////////////////////////////////////////////
void ConfigTouches::accederTouches(int &haut, int &droite, int &bas, int &gauche)
{
	haut = _haut;
	droite = _droite;
	bas = _bas;
	gauche = _gauche;
}


////////////////////////////////////////////////////////////////////////
/// @fn void ConfigTouches::setToucheHaut()
/// Cette methode permet de modifier la touche correspondant à la
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
/// Cette methode permet de modifier la touche correspondant à la
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
/// Cette methode permet de modifier la touche correspondant à la
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
/// Cette methode permet de modifier la touche correspondant à la
/// direction "gauche" du joueur 2.
/// @param[in] touche : nouvelle touche gauche
/// @return void
////////////////////////////////////////////////////////////////////////
void ConfigTouches::setToucheGauche(int touche)
{
	_gauche = touche;
}

////////////////////////////////////////////////////////////////////////
/// @fn void ConfigTouches::setTouches()
/// Cette methode permet de modifier les touches correspondants aux
/// différentes directions.
/// @param[in] haut : nouvelle touche haut
/// @param[in] droite : nouvelle touche droite
/// @param[in] bas : nouvelle touche bas
/// @param[in] gauche : nouvelle touche gauche
/// @return void
////////////////////////////////////////////////////////////////////////
void ConfigTouches::setTouches(int haut, int droite, int bas, int gauche)
{
	_haut = haut;
	_droite = droite;
	_bas = bas;
	_gauche = gauche;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
