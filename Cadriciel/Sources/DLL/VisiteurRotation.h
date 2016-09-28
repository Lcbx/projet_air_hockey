#pragma once
#ifndef VISITEUR_ROTATION_H
#define VISITEUR_ROTATION_H

#include <iostream>
#include <string>

#include "Visiteur.h"




class VisiteurRotation : public Visiteur
{
	enum Etats { DETERMINER_CENTRE, APPLIQUER_ROTATION };
	Etats etat_;
	float angle_{0.f};
	int nbrNoeudsVisites_{0};
	glm::vec3 posCentre_{0.f,0.f,0.f};

public:
	VisiteurRotation();
	void rotate(float angle);
	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);
	

	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);

};
#endif

