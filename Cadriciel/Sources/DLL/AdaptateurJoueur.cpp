#include "AdaptateurJoueur.h"
#include "FacadeModele.h"

/// @fn AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur)
/// @brief Constructeur par défaut, représente un cas nul
AdaptateurJoueur::AdaptateurJoueur() {
	this->nomJoueur = "";
	this->isHuman = true;
}

/// @fn AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur)
/// @brief Constructeur par nom
/// @param nomJoueur : Nom du joueur
AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur) {
	this->nomJoueur = nomJoueur;
	this->isHuman = true;
}

/// @fn AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur, JoueurVirtuel joueurVirtuel)
/// @brief Constructeur par nom et joueur virtuel
/// @param nomJoueur : Nom du joueur
/// @param joueurVirtuel : Joueur virtuel lié
AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur, Profil joueurVirtuel) {
	this->nomJoueur = nomJoueur;
	this->joueurVirtuel = joueurVirtuel;
	this->isHuman = false;
}

/// @fn AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur, bool estHumain, std::string joueurVirtuel)
/// @brief Constructeur par nom et joueur virtuel
/// @param nomJoueur : Nom du joueur
/// @param estHumain : Si le joueur est humain
/// @param nomJoueurVirtuel : Nom du profil du joueur virtuel
AdaptateurJoueur::AdaptateurJoueur(std::string nomJoueur, bool estHumain, std::string nomJoueurVirtuel) {
	this->nomJoueur = nomJoueur;
	this->isHuman = estHumain;
	this->joueurVirtuel = FacadeModele::obtenirInstance()->getConfigProfils()->getProfil(nomJoueurVirtuel);
}

/// @fn AdaptateurJoueur::estHumain()
/// @brief Permet de savoir si un joueur n'est pas un ordinateur
/// @return Si le joueur est humain
bool AdaptateurJoueur::estHumain() {
	return isHuman;
}

/// @fn std::string AdaptateurJoueur::getNomJoueur()
/// @brief Permet d'obtenir le nom du joueur
/// @return Le nom du joueur
std::string AdaptateurJoueur::getNomJoueur() {
	return this->nomJoueur;
}

/// @fn Profil AdaptateurJoueur::Profil()
/// @brief Permet d'obtenir le profil du joueur virtuel
/// @return Le profil du joueur virtuel
Profil AdaptateurJoueur::getProfil() {
	return this->joueurVirtuel;
}