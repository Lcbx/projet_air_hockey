#pragma once
#ifndef VISITEUR_H
#define VISITEUR_H

#include <iostream>
#include <string>
#include <NoeudAbstrait.h>
#include <NoeudComposite.h>
#include <NoeudTypes.h>

#include "FacadeModele.h"

/*INCLURE LES AUTRES NOUEDS !!*/

using namespace std;


class FacadeModele;

class Visiteur
{
public:


	virtual void visiter(NoeudAbstrait* noeud) = 0;
	virtual void visiter(NoeudComposite* noeud) = 0;
	
	virtual void visiter(NoeudRondelle* noeud) = 0;
	virtual void visiter(NoeudMuret* noeud) = 0;
	virtual void visiter(NoeudBonus* noeud) = 0;
	virtual void visiter(NoeudMaillet* noeud) = 0;
	virtual void visiter(NoeudPortail* noeud) = 0;


};
#endif