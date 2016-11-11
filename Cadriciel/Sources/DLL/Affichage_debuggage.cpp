//////////////////////////////////////////////////////////////////////////////
/// @file Affichage_debuggage.cpp
/// @author Luc Courbariaux
/// @date 2016-10-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "Affichage_debuggage.h"

#include <iostream>
#include <iomanip>

////////////////////////////////////////////////////////////////////////
///
/// @fn Debug& Debug::obtenirInstance
///
/// cette fonction renvoie l'instance statique de la classe Debug (patron singleton)
///
/// @return Debug&.
///
////////////////////////////////////////////////////////////////////////
Debug& Debug::obtenirInstance()
{
	static Debug instance_;
	return instance_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Debug::Debug()
///
/// Cette fonction initialise l'objet Debug créé dont son compteur de temps interne
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Debug::Debug() {
	//les heures et les secondes du systeme d'exploitation
	time_t now = time(0);
	tm* ltm = localtime(&now);
	temps_ = *ltm;
	//les millisecondes du timer
	current_ = clock();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::actualiser()
///
/// Cette fonction effectue actualise le temps écoulé depuis la derniere actualisation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::actualiser() {
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void Debug::afficher(std::string message)
///
/// Cette fonction affiche le message passe en orgument accompagné d'un timestamp
///
/// @param[in] message : le message a afficher
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Debug::afficher(std::string message) {
	actualiser();
	std::cout << std::setfill('0') << std::setw(2) << temps_.tm_hour << ":"
		<< std::setfill('0') << std::setw(2) << temps_.tm_min << ":"
		<< std::setfill('0') << std::setw(2) << temps_.tm_sec << ":"
		<< std::setfill('0') << std::setw(3) << milli_ << " - "
		<< message << "\n";
}