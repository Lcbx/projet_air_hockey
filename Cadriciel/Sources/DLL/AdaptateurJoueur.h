#pragma once

#include "Profil.h"
#include <string>

/// @class AdaptateurJoueur
/// @brief Permet d'adapter un joueur virtuel et un joueur humain pour un tournoi
class AdaptateurJoueur {
private:
	Profil joueurVirtuel;
	bool isHuman;
	std::string nomJoueur;

public:
	/// Constructeur par défaut, représente un cas nul
	AdaptateurJoueur();

	/// Constructeur par nom
	AdaptateurJoueur(std::string nomJoueur);

	/// Constructeur par nom et joueur virtuel
	AdaptateurJoueur(std::string nomJoueur, Profil joueurVirtuel);

	/// Constructeur par nom, est humain et joueur virtuel
	AdaptateurJoueur(std::string nomJoueur, bool estHumain, std::string joueurVirtuel);

	/// Permet de savoir si un joueur est un ordinateur
	bool estHumain();

	/// Permet d'obtenir le nom du joueur
	std::string getNomJoueur();

	/// Permet d'obtenir le profil du joueur virtuel
	Profil AdaptateurJoueur::getProfil();
};
