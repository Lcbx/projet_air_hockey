#pragma once
#ifndef VISITEUR_DEPLACEMENT_H
#define VISITEUR_DEPLACEMENT_H

#include <iostream>
#include <string>

#include "Visiteur.h"




class VisiteurDeplacement : public Visiteur
{
	glm::vec3 dep_{0.f};
public:
	
	VisiteurDeplacement(glm::vec3 dep);

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);
	

	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);
	
};
#endif