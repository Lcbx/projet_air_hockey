#pragma once
#ifndef VISITEUR_SAUVEGARDE_H
#define VISITEUR_SAUVEGARDE_H

#include <iostream>
#include <string>

#include "Visiteur.h"
#include "tinyxml2.h"



class VisiteurSauvegarde : public Visiteur
{
	
public:
	VisiteurSauvegarde(tinyxml2::XMLElement* elem, tinyxml2::XMLDocument* doc)
		: elementXMLPere_(elem), documentXML_(doc)
	{
	}

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);

	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);

private:
	// Pointeur vers l'element XML du pere du noeud visit?
	tinyxml2::XMLElement* elementXMLPere_;

	// Pointeur vers le document XML dans lequel est enregistre l'arbre
	tinyxml2::XMLDocument* documentXML_;
};
#endif