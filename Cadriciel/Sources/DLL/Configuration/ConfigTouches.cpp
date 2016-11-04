//////////////////////////////////////////////////////////////////////////////
/// @file ConfigTouches.cpp
/// @author Arthur Daniel-Adde
/// @date 2016-10-21
///
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "ConfigTouches.h"
#include <iostream>

#include "Utilitaire.h"
#include "FacadeModele.h"

/// Nombre de calculs par image.
const int ConfigTouches::HAUTDEF{ 87 };
const int ConfigTouches::DROITEDEF{ 68 };
const int ConfigTouches::BASDEF{ 83 };
const int ConfigTouches::GAUCHEDEF{ 65 };

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::ConfigTouches()
///
/// Constructeur par d�faut de ConfigTouches
/// Charge le fichier de touches, si il existe
///
////////////////////////////////////////////////////////////////////////
ConfigTouches::ConfigTouches()
{

	chargerTouches();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::enregistrerTouches (int haut, int droite, int bas, int gauche)
///
/// Cette methode sauvegarde les touches du jour 2 actuelles dans
///  un �l�ment XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigTouches::enregistrerTouches(int haut, int droite, int bas, int gauche)
{
	_haut = haut;
	_droite = droite;
	_bas = bas;
	_gauche = gauche;

	tinyxml2::XMLDocument document;
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");

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

	// �crire dans le fichier
	document.SaveFile("touches.xml");
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::chargerTouches()
///
/// Cette methode charge les touches du jour 2 actuelles � partir 
/// d'un �l�ment XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigTouches::chargerTouches()
{
	// V�rification de l'existance du ficher
	if (!utilitaire::fichierExiste("touches.xml")) {
		// Si le fichier n'existe pas, on le cr�e.
		enregistrerTouches(HAUTDEF, DROITEDEF, BASDEF, GAUCHEDEF);
	}
	else {

		// Charge le fichier de configuration
		tinyxml2::XMLDocument document;
		document.LoadFile("touches.xml");

		// Obtenir le noeud 'Configuration'
		const tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
		if (elementConfiguration != nullptr) {

			// Obtenir l'�l�ment 'touches'
			const tinyxml2::XMLElement* elementTouches{ elementConfiguration->FirstChildElement("CTouches") };
			if (elementTouches != nullptr) {
				// Obtenir les attributs des touches
				if (elementTouches->QueryIntAttribute("TOUCHE_HAUT", &_haut) != tinyxml2::XML_SUCCESS ||
					elementTouches->QueryIntAttribute("TOUCHE_DROITE", &_droite) != tinyxml2::XML_SUCCESS ||
					elementTouches->QueryIntAttribute("TOUCHE_BAS", &_bas) != tinyxml2::XML_SUCCESS ||
					elementTouches->QueryIntAttribute("TOUCHE_GAUCHE", &_gauche) != tinyxml2::XML_SUCCESS) {
					std::cerr << "Erreur de chargement des touches" << std::endl;
				}
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
	_droite = DROITEDEF;
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
/// @fn void ConfigTouches::accederTouches()
/// Cette methode permet d'obtenir les touches correspondants aux
/// 4 directions
/// 
/// @return int[4] : [haut, droite, bas, gauche]
////////////////////////////////////////////////////////////////////////
void ConfigTouches::obtenirTouches(int *touches)
{
	touches[0] = _haut;
	touches[1] = _droite;
	touches[2] = _bas;
	touches[3] = _gauche;

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

////////////////////////////////////////////////////////////////////////
/// @fn void ConfigTouches::setTouches()
/// Cette methode permet de modifier les touches correspondants aux
/// diff�rentes directions.
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
