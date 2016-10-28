//////////////////////////////////////////////////////////////////////////////
/// @file Affichage_debuggage.h
/// @author Luc Courbariaux
/// @date 2016-10-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <ctime>
#include <string>

class Debug {

	///timestamp
	tm temps_;
	///les dernieres milli connues
	unsigned long current_;
	///les milli ecoules depuis current_
	unsigned long milli_;

	///initialisation
	Debug();

	///actualise le timestamp;
	void actualiser();

	///singleton
	Debug(Debug const&) = delete;
	void operator=(Debug const&) = delete;
	

public :

	///booleen pour affichage de collision
	bool afficherCollision = true;
	///booleen pour affichage de vitesse
	bool afficherVitesse = true;
	///booleen pour affichage de changement d'éclairage
	bool afficherLumieres = true;
	///booleen pour affichage de cercle d'attraction des portails
	bool afficherAttraction = true;

	///obtenirInstance
	static Debug& obtenirInstance();

	///affiche le timestamp
	void afficher(std::string message);

};

