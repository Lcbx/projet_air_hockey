#include "AdaptateurJoueur.h"

/// @fn AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur)
/// @brief Constructeur par nom
AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur) {
	this->nomJoueur = nomJoueur;
	this->joueurVirtuel = nullptr;
}

/// @fn AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur, JoueurVirtuel joueurVirtuel)
/// @brief Constructeur par nom et joueur virtuel
AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur, JoueurVirtuel joueurVirtuel) {
	this->nomJoueur = nomJoueur;
	this->joueurVirtuel = new JoueurVirtuel(joueurVirtuel);
}

/// @fn AdaptateurJoueur::estHumain()
/// @brief Permet de savoir si un joueur n'est pas un ordinateur
///
/// Vérifie si un joueur virtuel lui est lié. Si oui, c'est un ordinateur
/// @return 
bool AdaptateurJoueur::estHumain() {
	return this->joueurVirtuel != nullptr;
}

/// @fn std::string AdaptateurJoueur::getNomJoueur()
/// @brief Permet d'obtenir le nom du joueur
std::string AdaptateurJoueur::getNomJoueur() {
	return this->nomJoueur;
}

/// @fn std::string AdaptateurJoueur::getJoueurVirtuel()
/// @brief Permet d'obtenir le profil du joueur virtuel
JoueurVirtuel AdaptateurJoueur::getJoueurVirtuel() {
	return *(this->getJoueurVirtuel);
}