//////////////////////////////////////////////////////////////////////////////
/// @file ConfigProfils.cpp
/// @author Arthur Daniel-Adde
/// @date 2016-11-04
///
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "ConfigProfils.h"
#include <iostream>
#include "FacadeModele.h"

#include "../../../Commun/Externe/tinyxml2/include/tinyxml2.h"


// Nom du fichier de profils
const std::string ConfigProfils::FICHIER_PROFILS{ "profils.xml" };

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigProfils::ConfigProfils()
///
/// Constructeur par défaut de ConfigProfils
/// Charge le fichier de profil, si il existe
///
////////////////////////////////////////////////////////////////////////
ConfigProfils::ConfigProfils()
{
	chargerProfils();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigProfils::chargerProfils()
///
/// Cette methode charge la liste de profils à partir d'un fichier xml
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigProfils::chargerProfils()
{
	// Vérification de l'existance du ficher
	if (utilitaire::fichierExiste(FICHIER_PROFILS)) {

		// Charge le fichier de configuration
		tinyxml2::XMLDocument document;
		document.LoadFile(FICHIER_PROFILS.c_str());

		// Obtenir le noeud 'listeProfil'
		const tinyxml2::XMLElement* elementListeProfil{ document.FirstChildElement("listeProfil") };
		if (elementListeProfil != nullptr) {

			// Trouve le premier element profil
			const tinyxml2::XMLElement* elementProfil{ elementListeProfil->FirstChildElement() };
			while(elementProfil != nullptr) {
				// Ajoute l'element du fichier dans la liste de profils
				_listeProfils.push_back(Profil(
					elementProfil->Attribute("NOM"),
					elementProfil->DoubleAttribute("VITESSE"),
					elementProfil->DoubleAttribute("PROBABILITE")));
				// Passe au profil suivant
				elementProfil = elementListeProfil->NextSiblingElement();
			}

		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::setProfil (Profil profil)
///
/// Cette methode ajoute à la liste et sauvegarde un profil
///
/// @param[in] profil : Profil à ajouter à la liste
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigProfils::setProfil(Profil profil)
{
	setProfil(profil.getNom(), profil.getVitesse(), profil.getProbabilite());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::setProfil (std::string nom, double vitesse, double probabilite)
///
/// Cette methode ajoute à la liste et sauvegarde un profil
///
/// @param[in] nom : nom du profil à ajouter à la liste
/// @param[in] vitesse : vitesse du profil à ajouter à la liste
/// @param[in] probabilite : probabilite du profil à ajouter à la liste
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigProfils::setProfil(std::string nom, int vitesse, float probabilite)
{
	bool alreadyExist = false;

	// Parcourt la liste des profils
	for (std::list<Profil>::iterator it = _listeProfils.begin(); it != _listeProfils.end(); ++it) {
		// Si le profil existe déjà, le mettre à jour
		if (it->getNom() == nom.c_str()) {
			it->setNom(nom);
			it->setVitesse(vitesse);
			it->setProbabilite(probabilite);
			alreadyExist = true;
		}
	}

	// Ajoute le profil à la liste s'il n'existe pas encore
	if (!alreadyExist)
		_listeProfils.push_back(Profil(nom, vitesse, probabilite));


	// Créé un nouveau document XML si le fichier n'existe pas, ou le charge depuis le fichier dans le cas contraire
	tinyxml2::XMLDocument document;
	if (!utilitaire::fichierExiste(FICHIER_PROFILS))
		document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	else
		document.LoadFile(FICHIER_PROFILS.c_str());

	// Obtenir le noeud 'listeProfil', le créer si il n'existe pas
	tinyxml2::XMLElement* elementListeProfil{ document.FirstChildElement("listeProfil") };
	if (elementListeProfil == nullptr) {
		elementListeProfil = document.NewElement("listeProfil");
		document.LinkEndChild(elementListeProfil);
	}

	// 
	tinyxml2::XMLElement* elementProfil{ elementListeProfil->FirstChildElement(nom.c_str()) };
	if (elementListeProfil != nullptr) {
		elementProfil = document.NewElement(nom.c_str());
		elementListeProfil->LinkEndChild(elementProfil);
	}
	elementProfil->SetAttribute("NOM", nom.c_str());
	elementProfil->SetAttribute("VITESSE", vitesse);
	elementProfil->SetAttribute("PROBABILITE", probabilite);

	// Écrire dans le fichier
	document.SaveFile(FICHIER_PROFILS.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigTouches::supprimerProfil (std::string nom)
///
/// Cette methode supprime le profil spécifié
///
/// @param[in] nom : nom du profil à supprimer
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void ConfigProfils::supprimerProfil(std::string nom)
{
	bool exist = false;

	// Parcourt la liste des profils
	for (std::list<Profil>::iterator it = _listeProfils.begin(); it != _listeProfils.end(); ++it) {
		// Supprime le profil de la liste
		if (it->getNom() == nom.c_str()) {
			_listeProfils.erase(it);
			exist = true;
		}
	}

	// Si le profil existe bien, charger le fichier pour y supprimer le profil
	if (exist) {

		// Ouvrir le fichier
		tinyxml2::XMLDocument document;
		document.LoadFile(FICHIER_PROFILS.c_str());

		// Obtenir le noeud 'listeProfil'
		tinyxml2::XMLElement* elementListeProfil{ document.FirstChildElement("listeProfil") };

		// Supprimer le noeud
		elementListeProfil->DeleteChild(elementListeProfil->FirstChildElement(nom.c_str()));

		// Sauvegarder les changements dans le fichier
		document.SaveFile(FICHIER_PROFILS.c_str());
	}

}


////////////////////////////////////////////////////////////////////////
///
/// @fn Profil ConfigProfils::getProfil (std::string nom)
///
/// Cette methode retourne un profil selon son nom
///
/// @param[in] nom : nom du profil à retourner
///
/// @return le profil au nom spécifié, nommé ERREUR s'il n'existe pas
///
////////////////////////////////////////////////////////////////////////
Profil ConfigProfils::getProfil(std::string nom)
{
	// Parcourt la liste des profils
	for (std::list<Profil>::iterator it = _listeProfils.begin(); it != _listeProfils.end(); ++it) {
		// Si le profil existe déjà, le mettre à jour
		if (it->getNom() == nom.c_str()) {
			return *it;
		}
	}
	return Profil("ERREUR", 0, 0);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn double ConfigProfils::getVitesse (std::string nom)
///
/// Cette methode retourne la vitesse du maillet d'un profil selon son nom
///
/// @param[in] nom : nom du profil dont retourner la vitesse
///
/// @return la vitesse du profil au nom spécifié, ou NULL s'il n'existe pas
///
////////////////////////////////////////////////////////////////////////
double ConfigProfils::getVitesse(std::string nom)
{
	// Parcourt la liste des profils
	for (std::list<Profil>::iterator it = _listeProfils.begin(); it != _listeProfils.end(); ++it) {
		// Si le profil existe déjà, le mettre à jour
		if (it->getNom() == nom.c_str()) {
			return it->getVitesse();
		}
	}
	return NULL;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn double ConfigProfils::getProbabilite (std::string nom)
///
/// Cette methode retourne la probabilite d'agir passivement d'un profil
///  selon son nom
///
/// @param[in] nom : nom du profil dont retourner la probabilite
///
/// @return la probabilite du profil au nom spécifié, ou NULL s'il n'existe pas
///
////////////////////////////////////////////////////////////////////////
double ConfigProfils::getProbabilite(std::string nom)
{
	// Parcourt la liste des profils
	for (std::list<Profil>::iterator it = _listeProfils.begin(); it != _listeProfils.end(); ++it) {
		// Si le profil existe déjà, le mettre à jour
		if (it->getNom() == nom.c_str()) {
			return it->getProbabilite();
		}
	}
	return NULL;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<std::string> ConfigProfils::getNoms ()
///
/// Cette methode retourne un vecteur contenant tout les noms des profils
///
/// @return un vecteur de noms de profils
///
////////////////////////////////////////////////////////////////////////
std::vector<std::string> ConfigProfils::getNoms()
{
	// Rempli un vecteur des noms des profils
	std::vector<std::string> noms;
	for (std::list<Profil>::iterator it = _listeProfils.begin(); it != _listeProfils.end(); ++it) {
		noms.push_back(it->getNom());
	}

	// Retourne le vecteur
	return noms;
}