//////////////////////////////////////////////////////////////////////////////
/// @file ConfigDebug.cpp
/// @author Arthur Daniel-Adde
/// @date 2016-11-05
///
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "ConfigDebug.h"
#include <iostream>

#include "Utilitaire.h"
#include "FacadeModele.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigDebug::ConfigDebug()
///
/// Constructeur par défaut de ConfigDebug
/// Charge le fichier d'options de debug, si il existe
///
////////////////////////////////////////////////////////////////////////
ConfigDebug::ConfigDebug()
{

	chargerOptionsDebug();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigDebug::chargerOptionsDebug()
///
/// Cette methode charge les options de debug à partir du fichier
///  de configuration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigDebug::chargerOptionsDebug()
{
	bool optionsDebugDejaDefinies = false;
	// Vérification de l'existance du ficher
	if (utilitaire::fichierExiste("configuration.xml")) {

		// Charge le fichier de configuration
		tinyxml2::XMLDocument document;
		document.LoadFile("configuration.xml");

		// Obtenir le noeud 'Configuration'
		const tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
		if (elementConfiguration != nullptr) {

			// Obtenir l'élément 'CDebug'
			const tinyxml2::XMLElement* elementDebug{ elementConfiguration->FirstChildElement("CDebug") };
			if (elementDebug != nullptr) {
				// Obtenir les attributs des options de debug
				if (elementDebug->QueryBoolAttribute("IS_DEBUG_ACTIF", &_isDebugActif) != tinyxml2::XML_SUCCESS ||
					elementDebug->QueryBoolAttribute("SHOW_COLLISION_RONDELLE", &_showCollisionRondelle) != tinyxml2::XML_SUCCESS ||
					elementDebug->QueryBoolAttribute("SHOW_VITESSE_RONDELLE", &_showVitesseRondelle) != tinyxml2::XML_SUCCESS ||
					elementDebug->QueryBoolAttribute("SHOW_ECLAIRAGE", &_showEclairage) != tinyxml2::XML_SUCCESS ||
					elementDebug->QueryBoolAttribute("SHOW_ATTRACTION_PORTAIL", &_showAttractionPortail) != tinyxml2::XML_SUCCESS) {
					std::cerr << "Erreur de chargement des options de debug" << std::endl;
				}
				else
					optionsDebugDejaDefinies = true;
			}
		}
	}
	// Si les options de debug n'ont pas pu être chargées, utiliser les valeurs par défaut
	if (!optionsDebugDejaDefinies)
	{
		_isDebugActif = false;
		_showCollisionRondelle = false;
		_showVitesseRondelle = false;
		_showEclairage = false;
		_showAttractionPortail = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigDebug::setOptionsDebug (attributs...)
///
/// Cette methode sauvegarde les options de debug dans le fichier de
///  configuration.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigDebug::setOptionsDebug(bool isDebugActif, bool showCollisionRondelle, bool showVitesseRondelle, bool showEclairage, bool showAttractionPortail)
{
	_isDebugActif = isDebugActif;
	_showCollisionRondelle = showCollisionRondelle;
	_showVitesseRondelle = showVitesseRondelle;
	_showEclairage = showEclairage;
	_showAttractionPortail = showAttractionPortail;

	// Créer un nouveau document XML si le fichier n'existe pas, ou le charger depuis le fichier dans le cas contraire
	tinyxml2::XMLDocument document;
	if (!utilitaire::fichierExiste("configuration.xml"))
		document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	else
		document.LoadFile("configuration.xml");

	// Obtenir le noeud 'configuration', le créer si il n'existe pas
	tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
	if (elementConfiguration == nullptr) {
		elementConfiguration = document.NewElement("configuration");
		document.LinkEndChild(elementConfiguration);
	}


	// Obtenir le noeud 'CDebug', le créer si il n'existe pas
	tinyxml2::XMLElement* elementDebug{ elementConfiguration->FirstChildElement("CDebug") };
	if (elementDebug == nullptr) {
		elementDebug = document.NewElement("CDebug");
		elementConfiguration->LinkEndChild(elementDebug);
	}

	// Enregistrer les valeurs des options de jeu dans les attributs du noeud 'CJeu'
	elementDebug->SetAttribute("IS_DEBUG_ACTIF", _isDebugActif);
	elementDebug->SetAttribute("SHOW_COLLISION_RONDELLE", _showCollisionRondelle);
	elementDebug->SetAttribute("SHOW_VITESSE_RONDELLE", _showVitesseRondelle);
	elementDebug->SetAttribute("SHOW_ECLAIRAGE", _showEclairage);
	elementDebug->SetAttribute("SHOW_ATTRACTION_PORTAIL", _showAttractionPortail);

	// Sauvegarder les changements dans le fichier
	document.SaveFile("configuration.xml");
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ConfigDebug::isDebugActif()
/// Cette methode renvoie vrai si le debug est actif
/// @return l'etat de l'option "Activer le debogage"
////////////////////////////////////////////////////////////////////////
bool ConfigDebug::isDebugActif()
{
	return _isDebugActif;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ConfigDebug::showCollisionRondelle()
/// Cette methode renvoie vrai si un message de debug doit etre affiché
///  suite à la collision entre la rondelle et un objet
/// @return l'etat de l'option "Collision entre la rondelle et un objet"
////////////////////////////////////////////////////////////////////////
bool ConfigDebug::showCollisionRondelle()
{
	return _showCollisionRondelle;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ConfigDebug::showVitesseRondelle()
/// Cette methode renvoie vrai si la vitesse de la rondelle doit être
/// affichée suite à une collision
/// @return l'etat de l'option "Vitesse de la rondelle après
///          une collision"
////////////////////////////////////////////////////////////////////////
bool ConfigDebug::showVitesseRondelle()
{
	return _showVitesseRondelle;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ConfigDebug::showEclairage()
/// Cette methode renvoie vrai si un message de debug doit etre affiché
///  lors de l'activation ou de la désactivation d'un eclairage
/// @return l'etat de l'option "Activation ou désactivation
///         d’un éclairage"
////////////////////////////////////////////////////////////////////////
bool ConfigDebug::showEclairage()
{
	return _showEclairage;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ConfigDebug::showAttractionPortail()
/// Cette methode renvoie vrai si la limite d'attraction des portails
///  doit etre affichée en jeu
/// @return l'etat de l'option "Identification de la limite d’attraction
///         des portails"
////////////////////////////////////////////////////////////////////////
bool ConfigDebug::showAttractionPortail()
{
	return _showAttractionPortail;
}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
