///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.h
/// @author Wajdi Gharsalli
/// @date 2016-09-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef VISITEUR_ROTATION_H
#define VISITEUR_ROTATION_H

#include <iostream>
#include <string>

#include "Visiteur.h"




class VisiteurRotation : public Visiteur
{
	float angle_{0.f};
	glm::vec3 posCentre_{0.f,0.f,0.f};
	bool tester_ = true;	//s'il faut tester si la manipulation est viable
	bool effectuer_ = true;	//s'il faut effectuer la manipulation
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

