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


///initialisation
VisiteurCollision::VisiteurCollision(NoeudAbstrait* objet) {
	this->objet_ = objet;
	this->rayon_ = objet->obtenirRayon();
	this->position_ = objet->obtenirPositionRelative();
}

///fonction apppellee generalement
InfoCollision& VisiteurCollision::calculerCollision() {
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
	return result_;
}

///donne la collision la plus pertinente avec une suite segments
aidecollision::DetailsCollision VisiteurCollision::collisionSegments(glm::vec3 ensemble[], int nombre) {
	//determine la collision pour chacun des segments
	aidecollision::DetailsCollision detail = { aidecollision::COLLISION_AUCUNE, glm::vec3(0,0,0), 0 };
	for (int i = 0; i<nombre; i++) {
		aidecollision::DetailsCollision temp = aidecollision::calculerCollisionSegment( ensemble[ i%nombre ], ensemble[ (i+1)%nombre ], position_, rayon_ );
		if (temp.type != aidecollision::COLLISION_AUCUNE && temp.enfoncement > detail.enfoncement) detail = temp;
	}
	std::cout << "collision " << detail.type << "\n";
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

	//trouve la boite englobante du muret
	utilitaire::BoiteEnglobante boite = utilitaire::calculerBoiteEnglobante(*noeud->getModele());

	//reoriente les coorodonnnées de la boite dans notre repere
	double rayon = max(abs(boite.coinMax.x - boite.coinMin.x), abs(boite.coinMin.y - boite.coinMax.y)) / 2;
	glm::dvec3 scale = noeud->getScale();
	glm::dvec3 left{ -(rayon * scale.x), 0, 0 };
	glm::dvec3 right{ (rayon * scale.x), 0, 0 };
	//ajuste l'angle
	double angle = noeud->getAngle();
	glm::dvec3 pos = noeud->obtenirPositionRelative();
	left = utilitaire::rotater(left, angle) + pos;
	right = utilitaire::rotater(right, angle) + pos;

	//les coins de la boite
	glm::vec3 coins[4] = {	left,
							{ left.x, right.y, 0 },
							{ right.x, left.y, 0 },
							right };

	//retourne la collision la plus pertinente
	return collisionSegments(coins, 4);
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
