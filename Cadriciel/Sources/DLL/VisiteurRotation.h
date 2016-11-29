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



///////////////////////////////////////////////////////////////////////////
/// @class VisiteurRotation
/// @brief Cette classe contient des m�thodes permettant d'appliquer
///        une rotation a un noeud
///
/// @author Luc Courbariaux
/// @date 2016-09-25
//////////////////////////////////////////////////////////////////////////
class VisiteurRotation : public Visiteur
{
	float angle_{0.f};
	glm::vec3 posCentre_{0.f,0.f,0.f};
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

	/// @fn bool reussi()
	/// @brief Permet de v�rifier si l'op�ration a pu �tre effectu�e ou non
	/// @return Vrai si l'op�ration s'est produite, faux sinon
	bool reussi() { return effectuer_; }
};
#endif

