///////////////////////////////////////////////////////////////////////////////
/// @file Profil.cpp
/// @author Arthur
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "Profil.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"

/// @brief Nom par défaut pour un profil
const std::string Profil::NOM_DEFAUT{ "defaut" };

/// @fn Profil::Profil()
/// @brief Constructeur par défaut
Profil::Profil() { }

/// @fn Profil::Profil(std::string nom, double vitesse, double probabilite)
/// @brief Constructeur par paramètres
/// @param nom : Nom du profil
/// @param vitesse : Vitesse du joueur virtuel
/// @param probabilite : Probabilité de d'agir passivement
Profil::Profil(std::string nom, double vitesse, double probabilite)
{
	nom_ = nom;
	vitesse_ = vitesse;
	probabilite_ = probabilite;
}



////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn void Profil::setNom(double vitesse)
///
/// Cette fonction permet de modifier le nom du profil
///
/// param[in] nom : le nouveau nom du profil
///
/// @return void
/////////////////////////////////////////////////////////////////////////////////////////////////
void Profil::setNom(std::string nom)
{
	nom_ = nom;
}


////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn double Profil::getNom()
///
/// Cette fonction permet d'obtenir le nom du profil
///			
/// @return std::string nom : le nom du profil
/////////////////////////////////////////////////////////////////////////////////////////////////
std::string Profil::getNom()
{
	return nom_;
}


////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn void Profil::setVitesse(double vitesse)
///
/// Cette fonction permet de modifier la vitesse du maillet d'un profil
///
///param[in] vitesse : la vitesse de deplacement du maillet
///
/// @return void
/////////////////////////////////////////////////////////////////////////////////////////////////
void Profil::setVitesse(double vitesse)
{
	vitesse_ = vitesse;
}


////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn int Profil::getVitesse()
///
/// Cette fonction permet d'obtenir la vitesse du maillet d'un profil
///			
/// @return double vitesse : la vitesse de deplacement du maillet
/////////////////////////////////////////////////////////////////////////////////////////////////
int Profil::getVitesse()
{
	return vitesse_;
}


////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn void Profil::setProbabilite(double probabilite)
///
/// Cette fonction permet de modifier la probabilite d'agir passivement d'un profil
///
///param[in] probabilite : la probabilite d'agir passivement
///
/// @return void
/////////////////////////////////////////////////////////////////////////////////////////////////
void Profil::setProbabilite(double probabilite)
{
		probabilite_ = probabilite;
}


////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn double Profil::getProbabilite()
///
/// Cette fonction permet d'obtenir la probabilite d'agir passivement d'un profil
///			
/// @return double probabilite : la probabilite d'agir passivement
/////////////////////////////////////////////////////////////////////////////////////////////////
float Profil::getProbabilite()
{
	return probabilite_;
}
