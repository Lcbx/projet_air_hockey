///////////////////////////////////////////////////////////////////////////////
/// @file JoueurVirtuel.cpp
/// @author Ali
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "JoueurVirtuel.h"
#include "FacadeModele.h"
#include "../ArbreRenduINF2990.h"

///
////////////////////////////////////////////////////////////////////////
///
/// @fn void JoueurVirtuel:: deplacerMailletVirtuel()
///
/// Cette fonction permet de controler le maillet virtuel
/// selon un algorithme
///
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////
void JoueurVirtuel::deplacerMailletVirtuel()
{	
	auto facade = FacadeModele::obtenirInstance();

	glm::vec3 positionRondelle = facade->obtenirArbreRenduINF2990()->chercher("rondelle")->obtenirPositionRelative();
	float rayonRondelle = facade->obtenirArbreRenduINF2990()->chercher("rondelle")->obtenirRayonModele();
	vitesse_ = vitesse_ / 100;
	//std::cout << "positionRondelle (" << positionRondelle.x << "," << positionRondelle.y << ")" << std::endl;

	NoeudAbstrait * mailletVirtuel = facade->obtenirArbreRenduINF2990()->obtenirMailletManuel();
	NoeudMaillet * maillet = (NoeudMaillet *) mailletVirtuel;
	glm::vec3 positionMaillet = mailletVirtuel->obtenirPositionRelative();
	glm::vec3 nouvellePositionMaillet;
	nouvellePositionMaillet = positionMaillet;

	//std::cout << "positionMaillet (" << positionMaillet.x << "," << positionMaillet.y << ")" << std::endl;

	float rayonMaillet = mailletVirtuel->obtenirRayonModele();
	glm::vec3 positionMailletTable = positionMaillet - rayonMaillet;

	glm::vec3 vecteurMailletRondelle = positionRondelle - positionMaillet;
	glm::vec3 vecteurUnitaireMailletRondelle = vecteurMailletRondelle / glm::length(vecteurMailletRondelle);

	if (positionRondelle.x > 0) // rondelle dans la zone du joueur humain
	{
		if (fabs(positionRondelle.y - positionMaillet.y) > 1.5)
		{
			if (positionRondelle.y > positionMaillet.y)			
				nouvellePositionMaillet.y = positionMaillet.y + vitesse_;				
			else
				nouvellePositionMaillet.y = positionMaillet.y - vitesse_;					
		}
		
		if (facade->obtenirArbreRenduINF2990()->getTable()->mailletDansZone1({ nouvellePositionMaillet.x - vitesse_, 0,0 },rayonMaillet))
			nouvellePositionMaillet.x = positionMaillet.x - vitesse_;
		
	}
	else // rondelle dans la zone du joueur virtuelle
	{
		//generalement tant il n'y a pas de collision il va deplacer vers le centre du maillet
		// tant que la distance entre le centre du maillet et celui de la rondelle n'est pas egale a rayonMaillet + rayonRondelle
		if (glm::distance(positionMaillet, positionRondelle) != (rayonMaillet + rayonRondelle))
		{
			double r = RandomMN(1.5, 3);
			// multiplier la puissance du tir par un nombre aleatoire entre 1.5 et 3
			nouvellePositionMaillet.x += vecteurUnitaireMailletRondelle.x * vitesse_*r;
			nouvellePositionMaillet.y += vecteurUnitaireMailletRondelle.y * vitesse_*r;
		}
	}
	// deplacer le maillet selon un probabilite
	if (agir())
	{
		// a la fin on teste si la nouvelle position est dans la zone du jeu
		if (facade->obtenirArbreRenduINF2990()->getTable()->mailletDansZone1(nouvellePositionMaillet, rayonMaillet))
			//mailletVirtuel->assignerPositionRelative(nouvellePositionMaillet);
			maillet->deplacer(nouvellePositionMaillet);
	}
		
}

////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn bool JoueurVirtuel::agir(double probabilite)
///
/// Cette fonction permet de savoir si le joueur virtuelle doit
/// agir (bouger) ou rester passive (rien faire) selon une certaine	probabilite
///
/// param[in]  probabilite : la probabilite d'etre passive (faire rien)
///
/// @return bool : si true le joueur virtuel agit , si false il fait rien
///
/////////////////////////////////////////////////////////////////////////////////////////////////
bool JoueurVirtuel::agir()
{
	int number = rand() % 100;
	//std::cout << "number = " << number <<"probabilite = "<< int(probabilite_ * 100) << std::endl;

	if ( number < int(probabilite_ * 100))
	{
		//std::cout << "Active" << std::endl;
		return true;
	}		
	else
	{
		//std::cout << "Passive" << std::endl;
		return false;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn double JoueurVirtuel::RandomMN(double M, double N)
///
/// Cette fonction genere un nombre aleatoire x ente M et N
/// M < x < N
///
/// param[in]  M,N : 
///
/// @return double
///
/////////////////////////////////////////////////////////////////////////////////////////////////
double JoueurVirtuel::RandomMN(double M, double N)
{
	return M + (rand() / (RAND_MAX / (N - M)));
}
////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void JoueurVirtuel::setVitesse(double vitesse)
///
/// Cette fonction permet de modifier la vitesse du maillet
///param[in]
///			vitesse : la vitesse de deplacement du maillet
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////////////////////////////
void JoueurVirtuel::setVitesse(double vitesse) 
{
	vitesse_ = vitesse;
}
////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn double JoueurVirtuel:getVitesse()
///
/// Cette fonction permet d'obtenir la vitesse du maillet
///param[in]
///			
/// @return double.
///
/////////////////////////////////////////////////////////////////////////////////////////////////
double JoueurVirtuel::getVitesse()
{
	return vitesse_;
}
////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void JoueurVirtuel::setProbabilite(double probabilite)
///
/// Cette fonction permet de modifier la probabilite du maillet
/// pour etre passif
///param[in]
///			probabilite : la probabilite pour rien faire
/// @return Aucune.
///
/////////////////////////////////////////////////////////////////////////////////////////////////
void JoueurVirtuel::setProbabilite(double probabilite)
{
	if (probabilite >= 0 || probabilite <= 1)
		probabilite_ = probabilite;
}
////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn double JoueurVirtuel::getProbabilite()
///
/// Cette fonction permet d'obtenir la probabilite d'etre passif
///param[in]
///			
/// @return double.
///
/////////////////////////////////////////////////////////////////////////////////////////////////
double JoueurVirtuel::getProbabilite()
{
	return probabilite_;
}
