#pragma once

#include <tuple>
#include <cmath>

///
/// @class Tournoi
/// @brief Permet de d�finir un tournoi � partir d'une liste de participant
///
/// S'occupe de d�finir des matchups pour un tournoi � partir d'une configuration
/// de joueurs initiale
///
template <typename T>
class Tournoi {
private:
	// La structure du matchup est similaire � celle d'un arbre
	// avec le gagnant � la case 0, les deux participants du matchup
	// en 2^1 + 0 et 2^1 + 1 et ainsi de suite
	std::pair<T*, int>* matchups;
	// La profondeur de l'arbre
	int matchupDepth;

	// La liste des participants
	T* participants;


public:
	/// Constructeur par d�faut
	Tournoi() = delete;

	/// Constructeur avec un ensemble de participants
	Tournoi(int nbJoueurs, T* participants);

	/// Permet d'obtenir le prochain matchup
	std::pair<T, T> obtenirProchainMatchup();

	/// Permet d'attribuer le score au prochain matchup
	/// (Le matchup est celui obtenu via obtenirProchainMatchup)
	T affecterScoreProchainMatchup(int participant1, int participant2);

	/// Permet de savoir si le tournoi est termin�
	bool prochainMatchupExiste();

	/// Permet d'obtenir l'arbre complet des matchups
	std::pair<T, int>* obtenirMatchups();
};

/// @fn Tournoi<T>::Tournoi(int nbJoueurs, T* participants)
/// @brief Permet de cr�er un tournoi � partir d'une liste de participants
///
/// Le tournoi est cr�� de fa�on � ce que tous les joueurs peuvent �tre plac�s
/// Sur la branche la plus profonde. Peut causer des probl�mes de pr�cision autour
template<typename T>
Tournoi<T>::Tournoi(int nbJoueurs, T* participants) {
	matchupDepth = ceil(log2(nbJoueurs)); // Counting the root as depth 0

	this->participants = new T[nbJoueurs];
	for (int i = 0; i < nbJoueurs; i++) {
		this->participants[i] = *(participants + i);
	}

	int length = pow(2, matchupDepth + 1) - 1;
	this->matchups = new std::pair<T*, int>[length];

	int basePos = pow(2, matchupDepth) - 1;
	for (int i = 0; i < nbJoueurs; i++) {
		this->matchups[basePos + i] = std::make_pair<T*, int>((participants + i), 0);
	}
}

/// @fn std::pair<T, T> Tournoi<T>::obtenirProchainMatchup()
/// @brief Permet d'obtenir le prochain matchup pour un tournoi
///
/// @return Une paire de participants, en ordre
///
/// Visite l'arbre en depth first afin de trouver un matchup qui ne poss�de pas
/// de parents (soit de gagnant). On consid�re que le matchup est gagn� si on
/// atteint le haut de l'arbre (la racine)
template<typename T>
std::pair<T, T> Tournoi<T>::obtenirProchainMatchup() {

}
