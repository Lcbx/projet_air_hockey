///////////////////////////////////////////////////////////////////////////////
/// @file BoiteCollisionAbstraite.h
/// @author Carl-Vincent Landry-Duval
/// @date 2016-09-28
/// @version 1.0
///
/// @addtogroup collision BoiteCollisionAbstraite
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __BOITE_COLLISION_ABSTRAITE_H__
#define __BOITE_COLLISION_ABSTRAITE_H__

#include "AideCollision.h"

class BoiteCollision;
class CylindreCollision;
class SphereCollision;


///////////////////////////////////////////////////////////////////////////
/// @class BoiteCollisionAbstraite
/// @brief Permet une approche orientée objet de la gestion de collision
///
/// @author Carl-Vincent Landry-Duval
/// @date 2016-09-28
///////////////////////////////////////////////////////////////////////////
class BoiteCollisionAbstraite {
private:

public:
	BoiteCollisionAbstraite() {};
	virtual ~BoiteCollisionAbstraite() {};

	////////////////////////////////////////////////////////////////////////////////
	/// @func virtual aidecollision::DetailsCollision collides(BoiteCollision boite)
	/// @param[in]  boite Boite délimitatrice de collision
	/// @param[in]  collisionAvecPoints     : Vrai si on veut les collisions
	///                                       avec les extrémités.
	/// @param[in]  constanteRebondissement : Constante de rebondissement de
	///                                       l'objet.
	/// @param[in]  constanteAmortissement  : Constante d'amortissement de
	///                                       l'objet.
	/// @param[in]  vitesse                 : Vitesse de l'objet en collision.
	/// @param[out] retourDetails           : Pointeur pour retourner les
	///                                       détails de la collision.
	/// @return Vecteur de force résultante de la collision
	/// Permet de détecter la collision entre un objet et une boîte de collision
	////////////////////////////////////////////////////////////////////////////////	
	virtual glm::dvec3 collides(
		const BoiteCollision& boite,
		bool              collisionAvecPoints,
		double            constanteRebondissement,
		double            constanteAmortissement,
		const glm::dvec3& vitesse,
		aidecollision::DetailsCollision* retourDetails = nullptr
	) = 0;

	////////////////////////////////////////////////////////////////////////////////
	/// @func virtual aidecollision::DetailsCollision collides(CylindreCollision boite)
	/// @param[in]  boite Boite délimitatrice de collision
	/// @param[in]  collisionAvecPoints     : Vrai si on veut les collisions
	///                                       avec les extrémités.
	/// @param[in]  constanteRebondissement : Constante de rebondissement de
	///                                       l'objet.
	/// @param[in]  constanteAmortissement  : Constante d'amortissement de
	///                                       l'objet.
	/// @param[in]  vitesse                 : Vitesse de l'objet en collision.
	/// @param[out] retourDetails           : Pointeur pour retourner les
	///                                       détails de la collision.
	/// @return Vecteur de force résultante de la collision
	/// Permet de détecter la collision entre un objet et une cylindre de collision
	////////////////////////////////////////////////////////////////////////////////	
	virtual glm::dvec3 collides(
		const CylindreCollision& boite,
		bool              collisionAvecPoints,
		double            constanteRebondissement,
		double            constanteAmortissement,
		const glm::dvec3& vitesse,
		aidecollision::DetailsCollision* retourDetails = nullptr
	) = 0;



	////////////////////////////////////////////////////////////////////////////////
	/// @func virtual aidecollision::DetailsCollision collides(SphereCollision boite)
	/// @param[in]  boite Boite délimitatrice de collision
	/// @param[in]  collisionAvecPoints     : Vrai si on veut les collisions
	///                                       avec les extrémités.
	/// @param[in]  constanteRebondissement : Constante de rebondissement de
	///                                       l'objet.
	/// @param[in]  constanteAmortissement  : Constante d'amortissement de
	///                                       l'objet.
	/// @param[in]  vitesse                 : Vitesse de l'objet en collision.
	/// @param[out] retourDetails           : Pointeur pour retourner les
	///                                       détails de la collision.
	/// @return Vecteur de force résultante de la collision
	/// Permet de détecter la collision entre un objet et une sphère de collision
	////////////////////////////////////////////////////////////////////////////////	
	virtual glm::dvec3 collides(
		const SphereCollision& boite,
		bool              collisionAvecPoints,
		double            constanteRebondissement,
		double            constanteAmortissement,
		const glm::dvec3& vitesse,
		aidecollision::DetailsCollision* retourDetails = nullptr
	) = 0;
};

#endif // !__BOITE_COLLISION_ABSTRAITE_H__