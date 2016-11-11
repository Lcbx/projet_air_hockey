#include "ConfigTournoi.h"
#include <tinyxml2.h>
#include "Utilitaire.h"

/// @brief Le nom du fichier tournoi
const std::string ConfigTournoi::FICHIER_TOURNOI("tournoi.xml");
/// @brief Le nom de la zone par défaut
const std::string ConfigTournoi::ZONE_DEFAUT("defaut");

/// @fn ConfigTournoi::ConfigTournoi()
/// @brief Constructeur par défaut
/// Ne fait rien
ConfigTournoi::ConfigTournoi() { }

/// @fn std::vector<AdaptateurJoueur> ConfigTournoi::obtenirJoueurs()
/// @brief Permet d'obtenir la liste des joueurs contenue dans le fichier config
/// @param[out] joueurs : Liste des joueurs
/// @param[out] nomZone : Nom de la zone
void ConfigTournoi::obtenirJoueurs(std::vector<AdaptateurJoueur> &joueurs, std::string &nomZone) {
	std::vector<AdaptateurJoueur> ret;
	if (utilitaire::fichierExiste(FICHIER_TOURNOI)) {
		tinyxml2::XMLDocument document;
		document.LoadFile(FICHIER_TOURNOI.c_str());

		const tinyxml2::XMLElement* root{ document.FirstChildElement("joueurs") };
		if (root != nullptr) {
			const tinyxml2::XMLElement* joueur{ root->FirstChildElement() };
			while (joueur != nullptr) {
				ret.push_back(AdaptateurJoueur(
					joueur->Attribute("nom"),
					joueur->BoolAttribute("esthumain"),
					joueur->Attribute("profil")
				));

				joueur = joueur->NextSiblingElement();
			}
		}

		const tinyxml2::XMLElement* zone{ document.FirstChildElement("zone") };
		nomZone = zone->Attribute("nom");
	}

	/// On remplis le reste de profils par défaut
	for (int i = ret.size(); i < NB_JOUEURS; i++) {
		ret.push_back(AdaptateurJoueur("", false, Profil::NOM_DEFAUT));
	}

	if (nomZone == "")
		nomZone = "defaut";

	joueurs = ret;
}

/// @fn void ConfigTournoi::sauvegarderJoueurs(std::vector<AdaptateurJoueur> joueurs)
/// @brief Permet de sauvegarder des joueurs pour un tournoi
/// @param joueurs : La liste des joueurs ciblé
/// @param nomZone : Nom de la zone
void ConfigTournoi::sauvegarderJoueurs(std::vector<AdaptateurJoueur> joueurs, std::string nomZone) {
	tinyxml2::XMLDocument document;
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");

	tinyxml2::XMLElement* listeJoueurs = document.NewElement("joueurs");
	document.LinkEndChild(listeJoueurs);
	for (AdaptateurJoueur j : joueurs) {
		tinyxml2::XMLElement* joueur = document.NewElement("joueur");
		joueur->SetAttribute("nom", j.getNomJoueur().c_str());
		joueur->SetAttribute("esthumain", j.estHumain());
		joueur->SetAttribute("profil", j.getProfil().getNom().c_str());
		listeJoueurs->LinkEndChild(joueur);
	}

	tinyxml2::XMLElement* zoneDeJeu = document.NewElement("zone");
	zoneDeJeu->SetAttribute("nom", nomZone.c_str());
	document.LinkEndChild(zoneDeJeu);

	document.SaveFile(FICHIER_TOURNOI.c_str());
}