///////////////////////////////////////////////////////////////////////////////
/// @file Visiteur.h
/// @author Wajdi Gharsalli
/// @date 2016-09-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef VISITEUR_H
#define VISITEUR_H

#include <iostream>
#include <string>
#include <NoeudAbstrait.h>
#include <NoeudComposite.h>
#include <NoeudTypes.h>

#include "FacadeModele.h"

/*INCLURE LES AUTRES NOEUDS !!*/

using namespace std;


class FacadeModele;


///////////////////////////////////////////////////////////////////////////
/// @class Visiteur
/// @brief Classe abstraite du patron visiteur
///
/// @author Wajdi Gharsalli
/// @date 2016-09-10
///////////////////////////////////////////////////////////////////////////
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