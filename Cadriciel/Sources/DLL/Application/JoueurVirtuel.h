///////////////////////////////////////////////////////////////////////////////
/// @file JoueurVirtuel.h
/// @author Ali
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#pragma once
//#include "../../../DLL/NoeudMaillet.h"

///////////////////////////////////////////////////////////////////////////
/// @class JoueurVirtuel
/// @brief Cette classe contient des méthodes permettant de deplacer le maillet
/// du joueur virtuel selon 2 strategies defensif et offensif
///
/// @autho Ali
/// @date 2016-10-28
///////////////////////////////////////////////////////////////////////////
class JoueurVirtuel  {
public:
	///// Constructeur par défaut.
	//JoueurVirtuel();
	//JoueurVirtuel(double vitesse, double probabilite);
	///// Destructeur.
	//virtual ~JoueurVirtuel();
	void deplacerMailletVirtuel();
	bool agir();
	// set, get functions
	void   setVitesse(double vitesse);
	double getVitesse();
	void   setProbabilite(double probabilite);
	double getProbabilite();
	double RandomMN(double M, double N);
		
private:
	double vitesse_{ 1. };
	double probabilite_{ 1. };
	
	


};
/// @}