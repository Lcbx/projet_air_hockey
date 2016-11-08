#pragma once

#include <tuple>
#include <vector>
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
	// Le premier int repr�sente la case dans le vecteur participant (-1 signifie que le matchup n'a pas eu lieu)
	// Le second int repr�sente le score du participant
	std::vector<std::pair<int, int>> matchups;
	
	// La profondeur de l'arbre
	int matchupDepth;
	
	// La liste des participants
	std::vector<T> participants;

	// Le nombre de participants
	size_t nbJoueurs;


public:
	/// Constructeur par d�faut
	Tournoi() = delete;

	/// Constructeur avec un ensemble de participants
	Tournoi(std::vector<T> participants);

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
	std::vector<std::pair<T, int>> obtenirMatchups(T value = T());

private:
	/// Permet d'obtenir la position du deuxi�me joueur du prochain matchup
	int positionProchainMatchup();

	/// Permet d'obtenir le participant � la position donn�e dans le tableau matchups
	T participantAuMatchup(int positionMatchup);

};

/// @fn Tournoi<T>::Tournoi(std::vector<T> paticipants)
/// @brief Permet de cr�er un tournoi � partir d'une liste de participants
///
/// Le tournoi est cr�� de fa�on � ce que tous les joueurs peuvent �tre plac�s
/// Sur la branche la plus profonde. Peut causer des probl�mes de pr�cision autour
template<typename T>
Tournoi<T>::Tournoi(std::vector<T> participants) {
	this->participants = participants; //La liste des participants
	this->nbJoueurs = this->participants.size();
	this->matchupDepth = (int) ceil(log2(this->nbJoueurs));

	if (log2(this->nbJoueurs) != this->matchupDepth)
		throw new std::invalid_argument("Le nombre de joueurs doit �tre un multiple de 2.");
	
	// La liste des pairings des participants
	this->matchups.resize((size_t) pow(2, matchupDepth + 1) - 1, { -1, 0 });

	// Les participants sont ajout�s � la fin de l'arbre
	int basePos = (int) pow(2, matchupDepth) - 1;
	for (int i = 0; i < this->nbJoueurs; i++)
		this->matchups[basePos + i] = { i, 0 };
}



/// @fn Tournoi<T>::~Tournoi()
/// @brief Permet de lib�rer la m�moire de l'arbre de tournoi
template<typename T>
Tournoi<T>::~Tournoi() { }

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
	int pos = this->positionProchainMatchup();
	return { this->participantAuMatchup(pos-1), this->participantAuMatchup(pos) };
}

/// @fn int Tournoi<T>::positionProchainMatchup()
/// @brief Permet d'obtenir la position du deuxi�me joueur dans le prochain matchup
///
/// @return La position du deuxi�me joueur dans le prochain matchup dans l'arbre de matchup
template<typename T>
int Tournoi<T>::positionProchainMatchup() {
	int pos = (int) pow(2, this->matchupDepth + 1) - 2;

	while (pos > 0 && (this->matchups[(pos + 1) / 2 - 1].first >= 0)) {
		pos -= 2; //On consid�re que tous les matchups sont remplis par d�faut
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
	int pos = this->positionProchainMatchup();
	this->matchups[pos - 1].second = scoreParticipant1;
	this->matchups[pos].second = scoreParticipant2;
	int posGagnant = (pos + 1) / 2 - 1;
	if (scoreParticipant1 > scoreParticipant2) {
		this->matchups[posGagnant].first = this->matchups[pos - 1].first;
	} else {
		this->matchups[posGagnant].first = this->matchups[pos].first;
	}

	return this->participantAuMatchup(posGagnant);
}


/// @fn T Tournoi<T>::prochainMatchupExiste()
/// @brief Permet de savoir si un gagnant existe pour le tournoi
///
/// @return Vrai s'il existe un prochain matchup, faux si le tournoi a �t� gagn�
template<typename T>
bool Tournoi<T>::prochainMatchupExiste() {
	return this->positionProchainMatchup() != 0;
}


/// @fn T Tournoi<T>::participantAuMatchup(int postionMatchup)
/// @brief Permet de conna�tre le joueur au matchup donn�
/// @param[in] int positionMatchup : Position selon le tableau de matchup
///
/// @return Le joueur du matchup
template<typename T>
T Tournoi<T>::participantAuMatchup(int positionMatchup) {
	int pos = this->matchups[positionMatchup].first;
	if (pos < 0)
		throw new std::logic_error("Le participant n'a pas encore �t� assign� au matchup");
	return this->participants[pos];
}


/// @fn T Tournoi<T>::obtenirMatchups(T value = T())
/// @brief Permet de conna�tre l'ensemble des matchups
/// @param[in] T value : Valeur par d�faut pour les cas nuls
///
/// @return Le vecteur des matchups (joueur et score)
template<typename T>
std::vector<std::pair<T, int>> Tournoi<T>::obtenirMatchups(T value = T()) {
	std::vector<std::pair<T, int>> ret;

	for (auto matchup : this->matchups) {
		std::pair<T, int> retMatchup({ value, matchup.second });

		if (matchup.first >= 0) 
			retMatchup.first = this->participants[matchup.first];

		ret.push_back(retMatchup);
	}

	return ret;
}
