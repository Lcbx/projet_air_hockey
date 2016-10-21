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
#include <iostream>
#include <iomanip>

class Debug {

	///booleen pour affichage de collision
	bool collision = false;
	///booleen pour affichage de vitesse
	bool vitesse_ = false;
	///booleen pour affichage de changement d'éclairage
	bool lumieres_ = false;
	///booleen pour affichage de cercle d'attraction des portails
	bool attraction_ = false;

	///timestamp
	tm temps_;
	///les dernieres milli connues
	unsigned long current_;
	///les milli ecoules depuis current_
	unsigned long milli_;

	///initialisation
	Debug() {
		//les heures et les secondes du systeme d'exploitation
		time_t now = time(0);
		tm* ltm = localtime(&now);
		temps_ = *ltm;
		//les millisecondes du timer
		current_ = clock();
	}

	///actualise le timestamp;
	void actualiser() {
		//actualise milli_
		milli_ = clock() - current_;
		//si on a depasse une seconde, on acualise tout le timestamp
		if (milli_ >= 1000) {
			//on ajoute les secondes ecoules
			temps_.tm_sec += (milli_ / 1000);
			//actualise milli_ en gardant les milli supplementaires
			milli_ = milli_ % 1000;
			//actualise le temps en milli actuel
			current_ = clock();
			//convertit le timestamp resultant en minutes/heures
			mktime(&temps_);
		}
	}

	///affiche le timestamp
	void afficher() {
		actualiser();
		std::cout	<< std::setfill('0') << std::setw(2) << temps_.tm_hour << ":"
					<< std::setfill('0') << std::setw(2) <<  temps_.tm_min << ":"
					<< std::setfill('0') << std::setw(2) << temps_.tm_sec << ":"
					<< std::setfill('0') << std::setw(3) << milli_ << " - \n";
	}

public :
	///test
	static void Do() { static Debug instance_; instance_.afficher(); }

};



