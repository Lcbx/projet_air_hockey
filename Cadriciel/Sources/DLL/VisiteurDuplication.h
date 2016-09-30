///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author Luc Courbariaux
/// @date 2016-09-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Visiteur.h"




class VisiteurDuplication : public Visiteur
{
	glm::vec3 posCentre_;
	glm::vec3 posActuelle_;

public:
	void fantomDuplicate(glm::vec3 point);
	void finalDuplicate(glm::vec3 point);

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);


	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);

};

