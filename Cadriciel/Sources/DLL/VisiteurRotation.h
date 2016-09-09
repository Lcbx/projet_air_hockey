#pragma once
#ifndef VISITEUR_ROTATION_H
#define VISITEUR_ROTATION_H

#include <iostream>
#include <string>

#include "Visiteur.h"




class VisiteurRotation : public Visiteur
{
public:


	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);


};
#endif

