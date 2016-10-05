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
#include <list>

#include "Visiteur.h"
#include "VisiteurDeplacement.h"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDuplication
/// @brief Cette classe contient des méthodes permettant de dupliquer
///        des moeuds
///
/// @author Luc Courbariaux
/// @date 2016-09-25
//////////////////////////////////////////////////////////////////////////
class VisiteurDuplication : public Visiteur
{
	glm::vec3 posCentre_ {0.f};
	glm::vec3 posActuelle_{ 0.f };
	
	bool tester_ = true;	//s'il faut tester si la manipulation est viable
	bool effectuer_ = true;	//s'il faut tester si la manipulation est viable

	//liste de noeuds
	///contient les originaux(selectionnés)
	std::list<NoeudAbstrait*> originaux_;
	///et les clones (non selectionnés)
	std::list<NoeudAbstrait*> nosClones_;

	VisiteurDeplacement visDep_;

public:

	VisiteurDuplication();

	void duplicate(glm::vec3 point);
	void actualise(glm::vec3 point);
	void finalise();
	void supprimerClones();

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);
	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);

};

