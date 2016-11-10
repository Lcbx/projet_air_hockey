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


////////////////////////////////////////////////////////////////////////
///
/// @fn InfoCollision& VisiteurCollision::calculerCollision(glm::vec3 position, double rayon, bool rondelle)
///
/// Cette fonction renvoie la collision la plus pertinente pour un objet rond a la position donnee ;
/// prend en compte s'il s'agit de la rondelle, sinon assume que c'est un maillet
///
/// @param[in]	position : la position de l'objet teste
///				rayon : le rayon de l'objet teste
///				rondelle : s'il s'agit de la rondelle.
///
/// @return InfoCollision&.
///
////////////////////////////////////////////////////////////////////////
InfoCollision& VisiteurCollision::calculerCollision(glm::vec3 position, double rayon, bool rondelle) {
	position_ = position;
	rayon_ = rayon;
	rondelle_ = rondelle;

	result_.objet = nullptr;
	result_.details = { aidecollision::COLLISION_AUCUNE, glm::vec3(0,0,0), 0 };

	//test des murs (table)
	auto table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getTable();
	//recupere les buts
	glm::vec3 droiteHaut, droiteBas, gaucheHaut, gaucheBas, milieu;
	table->getButs(1, droiteHaut, milieu, droiteBas);
	table->getButs(2, gaucheHaut, milieu, gaucheBas);
	// les 8 points de controle de la table
	/*
				p0----------p2----------p4
		[haut]	|						 |
				|						 |
	but gauche	p6			p8			p7 but droite
				|						 |
		[bas]	|						 |
				p1----------p3----------p5

	*/
#define p(arg) table->chercher(arg)->obtenirPositionRelative()
	std::array<glm::vec3, 5> haut = {
		gaucheHaut,
		p(0),
		p(2),
		p(4),
		droiteHaut
	};
	auto temp = collisionSegments( haut.data(), haut.size() );
	if (temp.type != aidecollision::COLLISION_AUCUNE) {
		result_.type = InfoCollision::MUR;
		result_.details = temp;
		return result_;
	}
	std::array<glm::vec3, 5> bas = {
		droiteBas,
		p(5),
		p(3),
		p(1),
		gaucheBas
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

////////////////////////////////////////////////////////////////////////
///
/// @fn DetailsCollision VisiteurCollision::collisionSegments(glm::vec3 ensemble[], int nombre)
///
/// Cette fonction donne la collision la plus pertinente avec une suite de segments
///
/// @param[in]	ensemble : un tableau de points
///				nombre : le nombre de points
///
/// @return DetailsCollision.
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision VisiteurCollision::collisionSegments(glm::vec3 ensemble[], int nombre) {
	//determine la collision pour chacun des segments
	aidecollision::DetailsCollision detail = { aidecollision::COLLISION_AUCUNE, glm::vec3(0,0,0), 0 };
	for (int i = 0; i<nombre-1; i++) {
		aidecollision::DetailsCollision temp = aidecollision::calculerCollisionSegment( ensemble[ i ], ensemble[ i+1 ], position_, rayon_ );
		if (temp.type != aidecollision::COLLISION_AUCUNE && temp.enfoncement > detail.enfoncement) {
			detail = temp;
			///std::cout << "collision " << detail.type << " segment n " << i << " enfoncement " << detail.enfoncement << "\n";
		}
	}
	return detail;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn DetailsCollision VisiteurCollision::collisionSegments(glm::vec3 ensemble[], int nombre)
///
/// Cette fonction calcule une collision avec un objet circulaire
///
/// @param[in]	ensemble : un tableau de points
///				nombre : le nombre de points
///
/// @return DetailsCollision.
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision VisiteurCollision::visiterNoeudCercle(NoeudAbstrait* noeud, float rayon) {
	//calcul de la collision entre les deux cercles 
	glm::vec3 position = noeud->obtenirPositionRelative();
	auto detail = aidecollision::calculerCollisionCercle(
		glm::vec2(position.x, position.y), rayon,
		glm::vec2(position_.x, position_.y), rayon_);
	///if(detail.type != aidecollision::COLLISION_AUCUNE) std::cout << "collision " << detail.type << " enfoncement " << detail.enfoncement << "\n";
	return detail;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn DetailsCollision VisiteurCollision::visiterNoeudQuadrilatere(NoeudAbstrait* noeud)
///
/// Cette fonction calcule une collission avec un objet rectangulaire
///
/// @param[in]	noeud : le noeud rectangulaire
///
/// @return DetailsCollision.
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision VisiteurCollision::visiterNoeudQuadrilatere(NoeudAbstrait* noeud) {

	//recupere la boite de collision
	std::array<glm::vec3, 5> coinsBoiteCollision;
	if (noeud->obtenirType() == "muret") coinsBoiteCollision = ((NoeudMuret*)noeud)->obtenirBoiteCollision();
	if (noeud->obtenirType() == "bonus") coinsBoiteCollision = ((NoeudBonus*)noeud)->obtenirBoiteCollision();
	
	//retourne la collision la plus pertinente
	return collisionSegments(coinsBoiteCollision.data(), coinsBoiteCollision.size());
}

void VisiteurCollision::visiter(NoeudAbstrait* noeud) {}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudComposite *noeud)
///
/// Cette fonction passe le visiteur aux enfant du noeud composite
///
/// @param[in]	noeud : le noeud composite
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudComposite *noeud) {
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepter(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudRondelle *noeud)
///
/// Cette fonction verifie une collision avec la rondelle
///
/// @param[in]	noeud : la rondelle
///
/// @return Aucun.
///
///////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudRondelle* noeud) {
	if(!rondelle_){
		auto detail = visiterNoeudCercle(noeud, noeud->obtenirRayon());
		if (detail.type != aidecollision::COLLISION_AUCUNE) {
			result_.type = InfoCollision::RONDELLE;
			result_.objet = noeud;
			result_.details = detail;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudMuret* noeud)
///
/// Cette fonction calcule une collission avec un muret
///
/// @param[in]	noeud : le muret
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudMuret* noeud) {
	auto detail = visiterNoeudQuadrilatere(noeud);
	if (detail.type != aidecollision::COLLISION_AUCUNE) {
		result_.type = InfoCollision::MUR;
		result_.objet = noeud;
		result_.details = detail;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudBonus* noeud)
///
/// Cette fonction calcule une collission avec un objet bonus
///
/// @param[in]	noeud : le bonus
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudBonus* noeud) {
	auto detail = visiterNoeudQuadrilatere(noeud);
	if (detail.type != aidecollision::COLLISION_AUCUNE) {
		result_.type = InfoCollision::BONUS;
		result_.objet = noeud;
		result_.details = detail;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudMaillet* noeud)
///
/// Cette fonction calcule une collission avec un maillet
///
/// @param[in]	noeud : le maillet
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudMaillet* noeud) {
	if (rondelle_) {
		auto detail = visiterNoeudCercle(noeud, noeud->obtenirRayon());
		if (detail.type != aidecollision::COLLISION_AUCUNE) {
			result_.type = InfoCollision::MAILLET;
			result_.objet = noeud;
			result_.details = detail;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudPortail* noeud)
///
/// Cette fonction calcule une collission avec un objet portail
///
/// @param[in]	noeud : le portail
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudPortail* noeud) {
	//on reduit la taille de la zone de collision pour eviter la sortie de jeu de rondelle
	auto detail = visiterNoeudCercle(noeud, noeud->obtenirRayon() * 0.8f );
	if (detail.type != aidecollision::COLLISION_AUCUNE) {
		result_.type = InfoCollision::PORTAIL;
		result_.objet = noeud;
		result_.details = detail;
	}
}




