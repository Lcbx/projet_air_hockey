#pragma once

#include <vector>
#include "AdaptateurJoueur.h"

/// @class ConfigTournoi
/// @brief Représente la listes des participants d'un tournoi
/// @author Carl-Vincent Landry-Duval
/// @date 2016-11-10
class ConfigTournoi {
private:
	/// Nom du fichier tournoi
	static const std::string FICHIER_TOURNOI;
	
	/// Nombre de joueurs générés par défaut
	static const int NB_JOUEURS = 4;

public:
	/// Nom de la zone par defaut
	static const std::string ZONE_DEFAUT;

	/// Constructeur par défaut
	ConfigTournoi();

	/// Permet d'obtenir la liste des joueurs stockée
	static void obtenirJoueurs(std::vector<AdaptateurJoueur> &joueurs, std::string &nomZone);

	/// Permet de sauvegarde la liste des joueurs donnée
	static void sauvegarderJoueurs(std::vector<AdaptateurJoueur> joueurs, std::string nomZone);
};