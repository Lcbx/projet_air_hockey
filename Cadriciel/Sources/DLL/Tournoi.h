#pragma once

///
/// @class Tournoi
/// @brief Permet de définir un tournoi à partir d'une liste de participant
///
/// S'occupe de définir des matchups pour un tournoi à partir d'une configuration
/// de joueurs initiale
///
template <class T>
class Tournoi {
private:
	// La structure du matchup est similaire à celle d'un arbre
	// avec le gagnant à la case 0, les deux participants du matchup
	// en 2^1 + 0 et 2^1 + 1 et ainsi de suite
	std::pair<T*, int>* matchups;

	// La liste des participants
	T* participants;

public:
	/// Constructeur par défaut
	Tournoi();

	/// Constructeur avec un ensemble de participants
	Tournoi(int nbJoueurs, T* participants);

	/// Permet d'obtenir le prochain matchup
	std::pair<T, T> obtenirProchainMatchup();

	/// Permet d'attribuer le score au prochain matchup
	/// (Le matchup est celui obtenu via obtenirProchainMatchup)
	T affecterScoreProchainMatchup(int participant1, int participant2);

	/// Permet de savoir si le tournoi est terminé
	bool prochainMatchupExiste();

	/// Permet d'obtenir l'arbre complet des matchups
	std::pair<T, int>[] obtenirMatchups();
};
