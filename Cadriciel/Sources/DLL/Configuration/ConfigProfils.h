//////////////////////////////////////////////////////////////////////////////
/// @file ConfigProfils.h
/// @author Arthur Daniel-Adde
/// @date 2016-11-04
///
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGPROFILS_H__
#define __CONFIGURATION_CONFIGPROFILS_H__

#include <list>
#include <vector>
#include "../Application/Profil.h"

///////////////////////////////////////////////////////////////////////////
/// @class ConfigProfils
/// @brief Représente la liste des profils de joueurs virtuels
///
/// @author Arthur Daniel-Adde
/// @date 2016-11-04
///////////////////////////////////////////////////////////////////////////
class ConfigProfils
{

public:
	/// Constructeur par défaut
	ConfigProfils();

	/// Charge les profils depuis le fichier, si il est disponible
	void chargerProfils();

	/// Ajoute le profil, ou le modifie si il existe déjà
	void setProfil(Profil profil);

	/// Ajoute le profil avec les attributs spécifiés, ou le modifie si un profil du même nom existe
	void setProfil(std::string nom, int vitesse, float probabilite);

	/// Supprime un profil d'après son nom
	void supprimerProfil(std::string nom);

	/// Obtient un profil selon son nom, ou un Profil nommé 'ERREUR' si il n'existe pas
	Profil getProfil(std::string nom);

	/// Obtient la vitesse d'un profil selon son nom, si il existe
	double getVitesse(std::string nom);

	/// Obtient la probabilite d'un profil selon son nom, si il existe
	double getProbabilite(std::string nom);

	/// Obtient un vecteur des noms des profils
	void getNoms(int *noms);

	/// Obtient le nombre de profils
	int getNombre();






private:

	/// Liste des profils
	std::list<Profil> _listeProfils;

	std::vector<std::string> _listeNoms;

	/// Nom du fichier de profils
	static const std::string FICHIER_PROFILS;



};
#endif