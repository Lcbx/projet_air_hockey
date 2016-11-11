//////////////////////////////////////////////////////////////////////////////
/// @file ConfigJeu.cpp
/// @author Arthur Daniel-Adde
/// @date 2016-11-05
///
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "ConfigJeu.h"
#include <iostream>

#include "Utilitaire.h"
#include "FacadeModele.h"

/// Nombre de buts par d�faut
const int ConfigJeu::NOMBRE_BUT_DEFAUT{ 2 };

/// Type de joueur par d�faut
const bool ConfigJeu::JOUEUR_TEST_EST_HUMAIN_DEFAUT{ false };

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigJeu::ConfigJeu()
///
/// Constructeur par d�faut de ConfigJeu
/// Charge le fichier d'options de jeu, si il existe
///
////////////////////////////////////////////////////////////////////////
ConfigJeu::ConfigJeu()
{

	chargerOptionsJeu();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigJeu::chargerOptionsJeu()
///
/// Cette methode charge les options de jeu � partir du fichier
///  de configuration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigJeu::chargerOptionsJeu()
{
	bool optionsJeuDejaDefinies = false;
	// V�rification de l'existance du ficher
	if (utilitaire::fichierExiste("donnees\\configuration.xml")) {

		// Charge le fichier de configuration
		tinyxml2::XMLDocument document;
		document.LoadFile("donnees\\configuration.xml");

		// Obtenir le noeud 'Configuration'
		const tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
		if (elementConfiguration != nullptr) {

			// Obtenir l'�l�ment 'Cjeu'
			const tinyxml2::XMLElement* elementJeu{ elementConfiguration->FirstChildElement("CJeu") };
			if (elementJeu != nullptr) {
				// Obtenir les attributs des options de jeu
				if (elementJeu->QueryIntAttribute("NOMBRE_BUT", &_optionsJeu.nbrBut) != tinyxml2::XML_SUCCESS ||
					elementJeu->QueryBoolAttribute("JOUEUR_TEST_EST_HUMAIN", &_optionsJeu.joueurTestEstHumain) != tinyxml2::XML_SUCCESS) {
					std::cerr << "Erreur de chargement des options de jeu" << std::endl;
				}
				else
					optionsJeuDejaDefinies = true;
			}
		}
	}
	// Si les options de jeu n'ont pas pu �tre charg�es, utiliser les valeurs par d�faut
	if (!optionsJeuDejaDefinies) {
		_optionsJeu.nbrBut = NOMBRE_BUT_DEFAUT;
		_optionsJeu.joueurTestEstHumain = JOUEUR_TEST_EST_HUMAIN_DEFAUT;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigJeu::setOptionsJeu (int nbrBut, bool joueurTestEstHumain)
///
/// Cette methode sauvegarde les options de jeu dans le fichier de
///  configuration.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigJeu::setOptionsJeu(int nbrBut, bool joueurTestEstHumain)
{
	_optionsJeu.nbrBut = nbrBut;
	_optionsJeu.joueurTestEstHumain = joueurTestEstHumain;

	// Cr�er un nouveau document XML si le fichier n'existe pas, ou le charger depuis le fichier dans le cas contraire
	tinyxml2::XMLDocument document;
	if (!utilitaire::fichierExiste("donnees\\configuration.xml"))
		document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	else
		document.LoadFile("donnees\\configuration.xml");

	// Obtenir le noeud 'configuration', le cr�er si il n'existe pas
	tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
	if (elementConfiguration == nullptr) {
		elementConfiguration = document.NewElement("configuration");
		document.LinkEndChild(elementConfiguration);
	}


	// Obtenir le noeud 'CJeu', le cr�er si il n'existe pas
	tinyxml2::XMLElement* elementJeu{ elementConfiguration->FirstChildElement("CJeu") };
	if (elementJeu == nullptr) {
		elementJeu = document.NewElement("CJeu");
		elementConfiguration->LinkEndChild(elementJeu);
	}

	// Enregistrer les valeurs des options de jeu dans les attributs du noeud 'CJeu'
	elementJeu->SetAttribute("NOMBRE_BUT", _optionsJeu.nbrBut);
	elementJeu->SetAttribute("JOUEUR_TEST_EST_HUMAIN", _optionsJeu.joueurTestEstHumain);

	// Sauvegarder les changements dans le fichier
	document.SaveFile("donnees\\configuration.xml");
}



////////////////////////////////////////////////////////////////////////
/// @fn OptionsJeu ConfigJeu::getOptionsJeu()
/// Cette methode permet d'obtenir une structure contenant les options
/// de jeu
/// @return une structure OptionsJeu
////////////////////////////////////////////////////////////////////////
struct OptionsJeu* ConfigJeu::getOptionsJeu()
{
	return &_optionsJeu;
}



////////////////////////////////////////////////////////////////////////
/// @fn int ConfigJeu::getNombreDeButs()
/// Cette methode permet d'obtenir le nombre de buts n�c�ssaire pour
///  gagner une partie
/// @return le nombre de buts
////////////////////////////////////////////////////////////////////////
int ConfigJeu::getNombreDeButs()
{
	return _optionsJeu.nbrBut;
}

////////////////////////////////////////////////////////////////////////
/// @fn bool ConfigJeu::joueurTestEstHumain()
/// Cette methode renvoie vrai si le joueur 2 du mode test est un joueur
///  humain, et renvoie faux si c'est un joueur virtuel
/// @return 'true' si le joueur test est humain
///         'false' si le joueur test est virtuel
////////////////////////////////////////////////////////////////////////
bool ConfigJeu::joueurTestEstHumain()
{
	return _optionsJeu.joueurTestEstHumain;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
