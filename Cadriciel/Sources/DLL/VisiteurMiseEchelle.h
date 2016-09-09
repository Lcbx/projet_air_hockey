#pragma once
#ifndef VISITEUR_MISEECHELLE_H
#define VISITEUR_MISEECHELLE_H

#include <iostream>
#include <string>

#include "Visiteur.h"




class VisiteurMiseEchelle : public Visiteur
{
public:


	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);


};
#endif


