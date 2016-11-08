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
	// Le second param�tre est le score attribu� lors du matchup
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

	/// Destructeur
	~Tournoi();

	/// Permet d'obtenir le prochain matchup
	std::pair<T, T> obtenirProchainMatchup();

	/// Permet d'attribuer le score au prochain matchup
	/// (Le matchup est celui obtenu via obtenirProchainMatchup)
	T affecterScoreProchainMatchup(int scoreParticipant1, int scoreParticipant2);

	/// Permet de savoir si le tournoi est termin�
	bool prochainMatchupExiste();

	/// Permet d'obtenir l'arbre complet des matchups
	std::pair<T, int>* obtenirMatchups();

private:
	/// Permet d'obtenir la position du deuxi�me joueur du prochain matchup
	int positionProchainMatchup();

	/// Permet de mettre un gagnant par d�faut si un des deux joueurs est inexistant (null)
	void gagnerProchainMatchParDefaut();
};

/// @fn Tournoi<T>::Tournoi(int nbJoueurs, T* participants)
/// @brief Permet de cr�er un tournoi � partir d'une liste de participants
///
/// Le tournoi est cr�� de fa�on � ce que tous les joueurs peuvent �tre plac�s
/// Sur la branche la plus profonde. Peut causer des probl�mes de pr�cision autour
template<typename T>
Tournoi<T>::Tournoi(int nbJoueurs, T* participants) {
	this->matchupDepth = ceil(log2(nbJoueurs)); // Counting the root as depth 0

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

/// @fn Tournoi<T>::~Tournoi()
/// @brief Permet de lib�rer la m�moire de l'arbre de tournoi
///
/// Le tournoi est cr�� de fa�on � ce que tous les joueurs peuvent �tre plac�s
/// Sur la branche la plus profonde. Peut causer des probl�mes de pr�cision autour
template<typename T>
Tournoi<T>::~Tournoi() {
	delete[] this->matchups;
	delete[] this->participants;
}

/// @fn std::pair<T, T> Tournoi<T>::obtenirProchainMatchup()
/// @brief Permet d'obtenir le prochain matchup pour un tournoi
///
/// @return Une paire de participants, en ordre
///
/// Visite l'arbre en depth first afin de trouver un matchup qui ne poss�de pas
/// de parents (soit de gagnant). On consid�re que le matchup est gagn� si on
/// atteint le haut de l'arbre (la racine)
template<typename T> //TODO: Refactoriser
std::pair<T, T> Tournoi<T>::obtenirProchainMatchup() {
	this->gagnerProchainMatchParDefaut();
	int pos = this->positionProchainMatchup();
	return std::pair<T, T>(*(this->matchups[pos - 1].first), *(this->matchups[pos].first));
}


/// @fn void Tournoi<T>::gagnerProchainMatchParDefaut()
/// @brief Permet de d�finir un gagnant par d�faut pour le prochain matchup si un des participants est inexistant
///
/// V�rifie si les prochains matchups, de fa�on r�cursive, n'ont qu'un participant. Si c'est le cas, il gagne automatiquement le match
///
/// @return Rien
template<typename T> //TODO: Refactoriser
void Tournoi<T>::gagnerProchainMatchParDefaut() {
	int pos = this->positionProchainMatchup();
	while (this->matchups[pos].first == nullptr || this->matchups[pos - 1].first == nullptr) {
		this->matchups[(pos + 1)/ 2 - 1].first = (this->matchups[pos].first == nullptr) ? this->matchups[pos - 1].first : this->matchups[pos].first;
		pos = this->positionProchainMatchup();
	}
}

/// @fn int Tournoi<T>::positionProchainMatchup()
/// @brief Permet d'obtenir la position du deuxi�me joueur dans le prochain matchup
///
/// @return La position du deuxi�me joueur dans le prochain matchup dans l'arbre de matchup
template<typename T>
int Tournoi<T>::positionProchainMatchup() {
	int pos = pow(2, this->matchupDepth + 1) - 2;
	while (pos > 0 &&
		((this->matchups[(pos + 1) / 2 - 1].first != nullptr) ||
		(this->matchups[pos].first == nullptr && this->matchups[pos - 1].first == nullptr))) {
		pos -= 2;
	}

	return pos;
}

/// @fn T Tournoi<T>::affecterScoreProchainMatchup(int scoreParticipant1, int scoreParticipant2)
/// @brief Permet d'affecter le score au prochain matchup
/// @param[in] int scoreParticipant1 : Score du premier participant d�fini par obtenirProchainMatchup
/// @param[in] int scoreParticipant2 : Score du second participant d�fini par obtenirProchainMatchup
///
/// @return Le gagnant du matchup
///
/// Assigne le score au prochain matchup et place le joueur gagnant dans le matchup sup�rieur
template<typename T>
T Tournoi<T>::affecterScoreProchainMatchup(int scoreParticipant1, int scoreParticipant2) {
	this->gagnerProchainMatchParDefaut(); //TODO: Refactoriser
	int pos = this->positionProchainMatchup();
	this->matchups[pos - 1].second = scoreParticipant1;
	this->matchups[pos].second = scoreParticipant2;
	if (scoreParticipant1 > scoreParticipant2) {
		this->matchups[(pos + 1) / 2 - 1].first = this->matchups[pos - 1].first;
	} else {
		this->matchups[(pos + 1) / 2 - 1].first = this->matchups[pos].first;
	}

	return *(this->matchups[(pos + 1) / 2 - 1].first);
}


/// @fn T Tournoi<T>::affecterScoreProchainMatchup(int scoreParticipant1, int scoreParticipant2)
/// @brief Permet d'affecter le score au prochain matchup
/// @param[in] int scoreParticipant1 : Score du premier participant d�fini par obtenirProchainMatchup
/// @param[in] int scoreParticipant2 : Score du second participant d�fini par obtenirProchainMatchup
///
/// @return Le gagnant du matchup
///
/// Assigne le score au prochain matchup et place le joueur gagnant dans le matchup sup�rieur
template<typename T>
bool Tournoi<T>::prochainMatchupExiste() {
	this->gagnerProchainMatchParDefaut(); //TODO: Refactoriser
	return this->positionProchainMatchup() != 0;
}
