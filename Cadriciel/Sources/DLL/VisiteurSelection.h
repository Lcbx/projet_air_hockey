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


};
#endif
