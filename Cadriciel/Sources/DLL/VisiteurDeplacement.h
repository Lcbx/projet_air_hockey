#pragma once
#ifndef VISITEUR_DEPLACEMENT_H
#define VISITEUR_DEPLACEMENT_H

#include <iostream>
#include <string>

#include "Visiteur.h"




class VisiteurDeplacement : public Visiteur
{
public:
	

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);

	
};
#endif