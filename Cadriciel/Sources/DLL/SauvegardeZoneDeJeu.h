#pragma once
#ifndef __SAUVEGARDEZONEJEU_H__
#define __SAUVEGARDEZONEJEU_H__

#include <tinyxml2.h>

#include "Visiteur.h"

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
	static void creerArbre(tinyxml2::XMLDocument& document);

	/// Lit la zone de jeu actuelle
	static void lireArbre(const tinyxml2::XMLDocument& document);

	/// Lit un noeud XML.
	static void lireNoeudXML(const tinyxml2::XMLElement& element);

	/// Sauvegarde le noeudTable dans un élément XML
	static tinyxml2::XMLElement* sauvegarderTable(tinyxml2::XMLDocument& document);

	/// Restitue le noeudTable enregistré dans un élément XML
	static void restituerTable(const tinyxml2::XMLElement& element);

	/// Traduit un noeud XML d'un type spécifique en noeud de l'arbre de rendu.
	static void ajouterNoeudXML(const tinyxml2::XMLElement& element);


	//static void ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudComposite *noeud);
	//static void ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudBonus *noeud);
	//static void ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudPortail *noeud);
	//static void ajouterNoeudXML(const tinyxml2::XMLElement& element, NoeudMuret *noeud);

};

#endif

void restituerTable(const tinyxml2::XMLElement & element);
