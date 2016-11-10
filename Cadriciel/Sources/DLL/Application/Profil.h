///////////////////////////////////////////////////////////////////////////////
/// @file Profil.h
/// @author Arthur
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_PROFIL_H__
#define __CONFIGURATION_PROFIL_H__

#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class Profil
/// @brief Cette classe contient les informations d'un profil de joueur
/// virtuel
///
/// @autho Arthur
/// @date 2016-11-04
///////////////////////////////////////////////////////////////////////////
class Profil {
public:
	/// Nom par défaut
	static const std::string NOM_DEFAUT;

	/// Constructeur par défaut
	Profil();
	/// Constructeur par argument
	Profil(std::string nom, double vitesse, double probabilite);

	/// Mutateur de nom
	void setNom(std::string nom);
	/// Accesseur de nom
	std::string getNom();
	/// Mutateur de vitesse
	void  setVitesse(double vitesse);
	/// Accesseur de vitesse
	int getVitesse();
	/// Mutateur de probabilite
	void setProbabilite(double probabilite);
	/// Accesseur de probabilite
	float getProbabilite();


private:

	// Nom du profil
	std::string nom_;

	// Vitesse du maillet du profil
	int vitesse_;

	// Probabilite d'agir passivement du profil
	float probabilite_;




};
#endif
