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
	/// @fn AdaptateurJoueur(std::string nomJoueur)
	/// @brief Constructeur par nom
	AdaptateurJoueur(std::string nomJoueur) {
		this->nomJoueur = nomJoueur;
		this->joueurVirtuel = nullptr;
	}

	/// @fn AdaptateurJoueur(std::string nomJoueur, JoueurVirtuel joueurVirtuel)
	/// @brief Constructeur par nom et joueur virtuel
	AdaptateurJoueur(std::string nomJoueur, JoueurVirtuel joueurVirtuel) {
		this->nomJoueur = nomJoueur;
		this->joueurVirtuel = new JoueurVirtuel(joueurVirtuel);
	}


};