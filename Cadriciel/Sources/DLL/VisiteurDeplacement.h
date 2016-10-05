#pragma once
#ifndef VISITEUR_DEPLACEMENT_H
#define VISITEUR_DEPLACEMENT_H

#include <iostream>
#include <string>

#include "Visiteur.h"



///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeplacement
/// @brief Cette classe contient des méthodes permettant d'appliquer
///        un deplacement a un noeud
///
/// @author Luc Courbariaux
/// @date 2016-09-25
//////////////////////////////////////////////////////////////////////////
class VisiteurDeplacement : public Visiteur
{
	glm::vec3 dep_{0.f};
	bool tester_ = true;	//s'il faut tester si la manipulation est viable
	bool effectuer_ = true;	//s'il faut tester si la manipulation est viable
public:
	
	VisiteurDeplacement(glm::vec3 dep);
	void setDep(glm::vec3 dep);

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);
	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);
	
};
#endif