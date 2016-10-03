///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseEchelle.h
/// @author Wajdi Gharsalli
/// @date 2016-09-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef VISITEUR_MISEECHELLE_H
#define VISITEUR_MISEECHELLE_H

#include <iostream>
#include <string>

#include "Visiteur.h"




class VisiteurMiseEchelle : public Visiteur
{
public:

	VisiteurMiseEchelle();

	void mettreEchelle(float facteur);

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);
	

	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);


	float facteur_;

};
#endif


