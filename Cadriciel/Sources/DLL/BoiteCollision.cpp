///////////////////////////////////////////////////////////////////////////////
/// @file BoiteCollision.cpp
/// @author Carl-Vincent Landry-Duval
/// @date 2016-09-28
/// @version 1.0
///
/// @addtogroup collision BoiteCollision
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "BoiteCollision.h"

/// Collision avec une autre bo�te de collision
glm::dvec3 BoiteCollision::collides(
	const BoiteCollision& boite,
	bool              collisionAvecPoints,
	double            constanteRebondissement,
	double            constanteAmortissement,
	const glm::dvec3& vitesse,
	aidecollision::DetailsCollision* retourDetails //= nullptr
) {
	//Collision entre deux bo�tes de collision est la collision entre les diff�rentes bordures

	retourDetails = new aidecollision::DetailsCollision();
	retourDetails->direction = glm::dvec3{ 0,0,0 };
	retourDetails->enfoncement = 0;
	retourDetails->type = aidecollision::Collision::COLLISION_AUCUNE;

	for (auto droiteObjet : this->getSegments()) {
		for (auto droiteBoite : boite.getSegments()) {
			if (droiteObjet.intersectionSegment(droiteBoite.lirePoint(), droiteBoite.lireVecteur())) {
				retourDetails->type = aidecollision::Collision::COLLISION_SEGMENT;
				break;
			}
		}

		if (retourDetails->type != aidecollision::Collision::COLLISION_AUCUNE) break;		
	}

	return glm::dvec3{ 0,0,0 };
}

/// Collision avec une sph�re
glm::dvec3 BoiteCollision::collides(
	const SphereCollision& boite,
	bool              collisionAvecPoints,
	double            constanteRebondissement,
	double            constanteAmortissement,
	const glm::dvec3& vitesse,
	aidecollision::DetailsCollision* retourDetails //= nullptr
) {
	throw std::exception("Not implemented");
	return glm::dvec3{ 0,0,0 }; //TODO: Impl�menter
}

/// Collision avec un cylindre
glm::dvec3 BoiteCollision::collides(
	const CylindreCollision& boite,
	bool              collisionAvecPoints,
	double            constanteRebondissement,
	double            constanteAmortissement,
	const glm::dvec3& vitesse,
	aidecollision::DetailsCollision* retourDetails //= nullptr
) {
	throw std::exception("Not implemented");
	return glm::dvec3{ 0,0,0 }; //TODO: Impl�menter
}