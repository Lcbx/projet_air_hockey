///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurPointMilieu.h
/// @author Luc Courbariaux
/// @date 2016-09-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <list>
#include "Visiteur.h"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurPointMilieu
/// @brief Cette classe permet de déterminer le point au milieu
///		de la selection
///
/// @author Luc Courbariaux
/// @date 2016-09-25
//////////////////////////////////////////////////////////////////////////
class VisiteurPointMilieu : public Visiteur
{
	int nbrNoeudsVisites_;
	glm::vec3& posCentre_;
	std::list<NoeudAbstrait*> selection_;

public:
	VisiteurPointMilieu(glm::vec3& pointARendre);

	std::list<NoeudAbstrait*> getSelection();

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);


	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);

};