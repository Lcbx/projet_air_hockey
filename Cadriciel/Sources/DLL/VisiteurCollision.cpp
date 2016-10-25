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

	//test des murs (table)
	auto table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable();
	// les 8 points de controle de la table
	/*
	p0----------p2----------p4
	|						 |
	|						 |
	p6			p8			p7
	|						 |
	|						 |
	p1----------p3----------p5

	*/
#define p(arg) table->chercher(arg)->obtenirPositionRelative()
	std::array<glm::vec3, 5> haut = {
		p(6),
		p(0),
		p(2),
		p(4),
		p(7)
	};
	auto temp = collisionSegments( haut.data(), haut.size() );
	if (temp.type != aidecollision::COLLISION_AUCUNE) {
		result_.type = InfoCollision::MUR;
		result_.details = temp;
		return result_;
	}
	std::array<glm::vec3, 5> bas = {
		p(7),
		p(5),
		p(3),
		p(1),
		p(6)
	};
	temp = collisionSegments(bas.data(), bas.size());
	if (temp.type != aidecollision::COLLISION_AUCUNE) {
		result_.type = InfoCollision::MUR;
		result_.details = temp;
		return result_;
	}
#undef p

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(this);
	return result_;
}

///donne la collision la plus pertinente avec une suite segments
aidecollision::DetailsCollision VisiteurCollision::collisionSegments(glm::vec3 ensemble[], int nombre) {
	//determine la collision pour chacun des segments
	aidecollision::DetailsCollision detail = { aidecollision::COLLISION_AUCUNE, glm::vec3(0,0,0), 0 };
	for (int i = 0; i<nombre-1; i++) {
		aidecollision::DetailsCollision temp = aidecollision::calculerCollisionSegment( ensemble[ i ], ensemble[ i+1 ], position_, rayon_ );
		if (temp.type != aidecollision::COLLISION_AUCUNE && temp.enfoncement > detail.enfoncement) {
			detail = temp;
			//std::cout << "collision " << detail.type << " segment n " << i << " enfoncement " << detail.enfoncement << "\n";
		}
	}
	
	return detail;
}

///calcul de collision avec un objet circulaire
aidecollision::DetailsCollision VisiteurCollision::visiterNoeudCercle(NoeudAbstrait* noeud, float rayon) {
	//calcul de la collision entre les deux cercles 
	glm::vec3 position = noeud->obtenirPositionRelative();
	auto detail = aidecollision::calculerCollisionCercle(
		glm::vec2(position.x, position.y), rayon,
		glm::vec2(position_.x, position_.y), rayon_);
	//if(detail.type != aidecollision::COLLISION_AUCUNE) std::cout << "collision " << detail.type << " enfoncement " << detail.enfoncement << "\n";
	return detail;
}


///cacul de collission avec un objet rectangulaire
aidecollision::DetailsCollision VisiteurCollision::visiterNoeudQuadrilatere(NoeudAbstrait* noeud) {

	//recupere la boite de collision
	std::array<glm::vec3, 5> coinsBoiteCollision;
	if (noeud->obtenirType() == "muret") coinsBoiteCollision = ((NoeudMuret*)noeud)->obtenirBoiteCollision();
	if (noeud->obtenirType() == "bonus") coinsBoiteCollision = ((NoeudBonus*)noeud)->obtenirBoiteCollision();
	
	//retourne la collision la plus pertinente
	return collisionSegments(coinsBoiteCollision.data(), coinsBoiteCollision.size());
}

void VisiteurCollision::visiter(NoeudAbstrait* noeud) {}


void VisiteurCollision::visiter(NoeudComposite *noeud) {
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

void VisiteurCollision::visiter(NoeudRondelle* noeud) {
	if(objet_->obtenirType() != "rondelle"){
		auto detail = visiterNoeudCercle(noeud, noeud->obtenirRayon());
		if (detail.type != aidecollision::COLLISION_AUCUNE) {
			result_.type = InfoCollision::RONDELLE;
			result_.objet = noeud;
			result_.details = detail;
		}
	}
}


void VisiteurCollision::visiter(NoeudMuret* noeud) {
	auto detail = visiterNoeudQuadrilatere(noeud);
	if (detail.type != aidecollision::COLLISION_AUCUNE) {
		result_.type = InfoCollision::MUR;
		result_.objet = noeud;
		result_.details = detail;
	}
}

void VisiteurCollision::visiter(NoeudBonus* noeud) {
	auto detail = visiterNoeudQuadrilatere(noeud);
	if (detail.type != aidecollision::COLLISION_AUCUNE) {
		result_.type = InfoCollision::BONUS;
		result_.objet = noeud;
		result_.details = detail;
	}
}

void VisiteurCollision::visiter(NoeudMaillet* noeud) {
	if (objet_->obtenirType() != "maillet") {
		auto detail = visiterNoeudCercle(noeud, noeud->obtenirRayon());
		if (detail.type != aidecollision::COLLISION_AUCUNE) {
			result_.type = InfoCollision::MAILLET;
			result_.objet = noeud;
			result_.details = detail;
		}
	}
}

void VisiteurCollision::visiter(NoeudPortail* noeud) {
	//on reduit la taille de la zone de collision pour eviter la sortie de jeu de rondelle
	auto detail = visiterNoeudCercle(noeud, noeud->obtenirRayon() *0.6);
	if (detail.type != aidecollision::COLLISION_AUCUNE) {
		result_.type = InfoCollision::PORTAIL;
		result_.objet = noeud;
		result_.details = detail;
	}
}
