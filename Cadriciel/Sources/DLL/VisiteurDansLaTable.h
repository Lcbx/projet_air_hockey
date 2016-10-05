///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDansLaTable.h
/// @author Luc Courbariaux
/// @date 2016-10-05
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDansLaTable.h
/// @author Luc Courbariaux
/// @date 2016-10-05
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Visiteur.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDansLaTable
/// @brief Cette classe permet de déterminer si touts les noeuds 
///			sont bien dans la Table
///
/// @author Luc Courbariaux
/// @date 2016-09-25
//////////////////////////////////////////////////////////////////////////
class VisiteurDansLaTable : public Visiteur
{
	bool& result_;

public:

	VisiteurDansLaTable::VisiteurDansLaTable(bool& result);

	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);

	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);

};
