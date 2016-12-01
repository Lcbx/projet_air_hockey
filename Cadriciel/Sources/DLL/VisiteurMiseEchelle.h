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

#include <map>
#include "Visiteur.h"




class VisiteurMiseEchelle : public Visiteur
{
	bool effectuer = true;
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

	map<NoeudAbstrait*, glm::vec3> facteursOriginaux_;

	/// @fn bool reussi()
	/// @brief Permet de vérifier si l'opération a pu être effectuée ou non
	/// @return Vrai si l'opération s'est produite, faux sinon
	bool reussi() { return effectuer; }
};
#endif


