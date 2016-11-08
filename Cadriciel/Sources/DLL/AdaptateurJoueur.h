#pragma once

#include "JoueurVirtuel.h"
#include <string>

/// @class AdaptateurJoueur
/// @brief Permet d'adapter un joueur virtuel et un joueur humain pour un tournoi
class AdaptateurJoueur {
private:
	JoueurVirtuel *joueurVirtuel;
	std::string nomJoueur;

public:
	/// Constructeur par défaut ne doit pas être appelé
	AdaptateurJoueur() = delete;

	/// Constructeur par nom
	AdaptateurJoueur(std::string nomJoueur);

	/// Constructeur par nom et joueur virtuel
	AdaptateurJoueur(std::string nomJoueur, JoueurVirtuel joueurVirtuel);

	/// Permet de savoir si un joueur est un ordinateur
	bool estHumain();

	/// Permet d'obtenir le nom du joueur
	std::string getNomJoueur();

	/// Permet d'obtenir le profil du joueur virtuel
	JoueurVirtuel AdaptateurJoueur::getJoueurVirtuel();
};
