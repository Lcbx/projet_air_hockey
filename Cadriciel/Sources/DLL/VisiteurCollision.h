///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCollision.h
/// @author Luc Courbariaux
/// @date 2016-10-05
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Visiteur.h"
#include "AideCollision.h"


///////////////////////////////////////////////////////////////////////////
/// @class InfoCollision
/// @brief Cette classe contient les informations ayant trait à une collision
///
/// @author Luc Courbariaux
/// @date 2016-09-25
//////////////////////////////////////////////////////////////////////////
class InfoCollision {
public:
	///types d'objets rencontres
	enum TYPE { AUCUNE, MUR, BONUS, PORTAIL, MAILLET, RONDELLE };
	///type de l'objet en collision
	TYPE type = AUCUNE;
	///le pointeur a l'objet de la collision
	NoeudAbstrait* objet = nullptr;
	///détails de la collision
	aidecollision::DetailsCollision details { aidecollision::COLLISION_AUCUNE, glm::vec3(0,0,0), 0 };
};


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurCollision
/// @brief Cette classe permet de déterminer si il y a collision entre
///		l'objet circulaire passé en argument du constructeur et le reste des objets de l'arbre de rendu
///
/// @author Luc Courbariaux
/// @date 2016-09-25
//////////////////////////////////////////////////////////////////////////
class VisiteurCollision : public Visiteur
{

	friend class CollisionTest;

	///le resultat a rendre
	InfoCollision result_;
	///la position de l'objet dont on verifie les collisions
	glm::vec3 position_ ;
	///le rayon de l'objet qui verifie ses collisions
	double rayon_;
	///s'il s'agit de la rondelle
	bool rondelle_;

	///donne la collision la plus pertinente avec une suite segments
	aidecollision::DetailsCollision collisionSegments(glm::vec3 ensemble[], int nombre);
	///collision avec un objet de forme ronde
	aidecollision::DetailsCollision visiterNoeudCercle(NoeudAbstrait* noeud, float rayon);
	///collision avec un objet de forme rectangulaire
	aidecollision::DetailsCollision visiterNoeudQuadrilatere(NoeudAbstrait* noeud);

public:

	///renvoie la collision la plus pertinente pour un objet rond
	InfoCollision& calculerCollision(glm::vec3 position, double rayon, bool rondelle);


	virtual void visiter(NoeudAbstrait* noeud);
	virtual void visiter(NoeudComposite *noeud);

	virtual void visiter(NoeudRondelle* noeud);
	virtual void visiter(NoeudMuret* noeud);
	virtual void visiter(NoeudBonus* noeud);
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudPortail* noeud);

};