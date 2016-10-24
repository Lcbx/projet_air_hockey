///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCollision.cpp
/// @author Luc Courbariaux
/// @date 2016-10-05
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "VisiteurCollision.h"
#include "ArbreRenduINF2990.h"
#include "AideCollision.h"
#include <array>

///initialisation
VisiteurCollision::VisiteurCollision(NoeudAbstrait* objet) {
	this->objet_ = objet;
	this->rayon_ = objet->obtenirRayon();
	this->position_ = objet->obtenirPositionRelative();
}

///fonction apppellee generalement
InfoCollision& VisiteurCollision::calculerCollision() {
	result_.objet = nullptr;
	result_.details = { aidecollision::COLLISION_AUCUNE, glm::vec3(0,0,0), 0 };
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
	return result_;
}

///donne la collision la plus pertinente avec une suite segments
aidecollision::DetailsCollision VisiteurCollision::collisionSegments(glm::vec3 ensemble[], int nombre) {
	//determine la collision pour chacun des segments
	aidecollision::DetailsCollision detail = { aidecollision::COLLISION_AUCUNE, glm::vec3(0,0,0), 0 };
	for (int i = 0; i<nombre; i++) {
		aidecollision::DetailsCollision temp = aidecollision::calculerCollisionSegment( ensemble[ i%nombre ], ensemble[ (i+1)%nombre ], position_, rayon_ );
		if (temp.type != aidecollision::COLLISION_AUCUNE && temp.enfoncement > detail.enfoncement) {
			detail = temp;
			std::cout << "collision " << detail.type << " segment n " << i << " enfoncement " << detail.enfoncement << "\n";
		}
	}
	
	return detail;
}

///calcul de collision avec un objet circulaire
aidecollision::DetailsCollision VisiteurCollision::visiterNoeudCercle(NoeudAbstrait* noeud) {
	//calcul de la collision entre les deux cercles 
	//celui externe en premier
	double rayon = noeud->obtenirRayon();
	glm::vec3 position = noeud->obtenirPositionRelative();
	auto detail = aidecollision::calculerCollisionCercle(
		glm::vec2(position.x, position.y), rayon,
		glm::vec2(position_.x, position_.y), rayon_);
	std::cout << "collision " << detail.type << "\n";
	return detail;
}


///cacul de collission avec un objet rectangulaire
aidecollision::DetailsCollision VisiteurCollision::visiterNoeudQuadrilatere(NoeudAbstrait* noeud) {

	//recupere la boite de collision
	std::array<glm::vec3, 4> coinsBoiteCollision;
	if (noeud->obtenirType() == "muret") coinsBoiteCollision = ((NoeudMuret*)noeud)->obtenirBoiteCollision();
	if (noeud->obtenirType() == "bonus") coinsBoiteCollision = ((NoeudBonus*)noeud)->obtenirBoiteCollision();
	
	//retourne la collision la plus pertinente
	return collisionSegments(coinsBoiteCollision.data(), 4);
}

void VisiteurCollision::visiter(NoeudAbstrait* noeud) {}


void VisiteurCollision::visiter(NoeudComposite *noeud) {
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurCollision::visiter(NoeudRondelle* noeud) {
	if(objet_->obtenirType() != "rondelle"){
		auto detail = visiterNoeudCercle(noeud);
		if (detail.type != aidecollision::COLLISION_AUCUNE) {
			result_.objet = noeud;
			result_.details = detail;
		}
	}
}


void VisiteurCollision::visiter(NoeudMuret* noeud) {
	auto detail = visiterNoeudQuadrilatere(noeud);
	if (detail.type != aidecollision::COLLISION_AUCUNE) {
		result_.objet = noeud;
		result_.details = detail;
	}
}

void VisiteurCollision::visiter(NoeudBonus* noeud) {
	auto detail = visiterNoeudQuadrilatere(noeud);
	if (detail.type != aidecollision::COLLISION_AUCUNE) {
		result_.objet = noeud;
		result_.details = detail;
	}
}

void VisiteurCollision::visiter(NoeudMaillet* noeud) {
	if (objet_->obtenirType() != "maillet") {
		auto detail = visiterNoeudCercle(noeud);
		if (detail.type != aidecollision::COLLISION_AUCUNE) {
			result_.objet = noeud;
			result_.details = detail;
		}
	}
}

void VisiteurCollision::visiter(NoeudPortail* noeud) {
	auto detail = visiterNoeudCercle(noeud);
	if (detail.type != aidecollision::COLLISION_AUCUNE) {
		result_.objet = noeud;
		result_.details = detail;
	}
}
