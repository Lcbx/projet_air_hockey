#pragma once
#ifndef VISITEUR_SELECTION_H
#define VISITEUR_SELECTION_H

#include <iostream>
#include <string>

#include "Visiteur.h"




class VisiteurSelection : public Visiteur
{
public:


	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);
	

	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);

};
#endif
