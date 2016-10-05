#pragma once
#ifndef __SAUVEGARDEZONEJEU_H__
#define __SAUVEGARDEZONEJEU_H__

#include <tinyxml2.h>

///////////////////////////////////////////////////////////////////////////
/// @class SauvegardeZoneDeJeu
/// @brief Classe répertoriant les méthodes permettant de sauvegarder
///             et charger une zone de jeu.
///
///////////////////////////////////////////////////////////////////////////
class SauvegardeZoneDeJeu
{
public:

	/// Enregistre la zone de jeu actuelle
	static void creerArbre(tinyxml2::XMLDocument document);

	/// Lit la zone de jeu actuelle
	static void lireArbre(const tinyxml2::XMLDocument document);

	/// Lit un noeud XML.
	static void lireNoeudXML(const tinyxml2::XMLElement& element);

	/// Traduit un noeud XML d'un type spécifique en noeud de l'arbre de rendu.
	static void ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudComposite* noeud);
	static void ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudBonus* noeud);
	static void ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudPortail* noeud);
	static void ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudMuret* noeud);

};

#endif