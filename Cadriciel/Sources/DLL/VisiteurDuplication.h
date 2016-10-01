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



class VisiteurDuplication : public Visiteur
{
	glm::vec3 posCentre_ {0.f};
	glm::vec3 posActuelle_{ 0.f };

	std::list<NoeudAbstrait*> selection_;

	VisiteurDeplacement visDep_;

	void creerClones();
	void supprimerClones();

public:

	VisiteurDuplication();

	void duplicate(glm::vec3 point);
	void actualiser(glm::vec3 point);
	

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);


	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);

};

